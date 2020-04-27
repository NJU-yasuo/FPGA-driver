#include "util.h"
#include <sys/stat.h>
#include <errno.h>

static bool __HAS_INIT_IP = false;
static void *peripheral_virtual_addr_base = NULL;
static int dev_mem_fd = 0;
extern void *vir_addr_base;

bool init_cnn_accelerator()
{
	if (__HAS_INIT_IP == true)
	{
		vir_addr_base = peripheral_virtual_addr_base;
		return true;
	}
	if (map_ip_to_user_space() != true)
	{
		__HAS_INIT_IP = false;
		return false;
	}
	__HAS_INIT_IP = true;
	vir_addr_base = peripheral_virtual_addr_base;
	return true;
}

bool map_ip_to_user_space()
{
	if ((dev_mem_fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1)
	{
		printf("ERROR: could not open \"/dev/mem\"...\n");
		return false;
	}
	peripheral_virtual_addr_base = mmap(NULL, HPS_H2F_LW_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, dev_mem_fd, HPS_H2F_LW_BASE);

	if (peripheral_virtual_addr_base == MAP_FAILED)
	{
		printf("ERROR: mmap() failed...\n");
		close(dev_mem_fd);
		return false;
	}

	return true;
}

void *get_peripheral_virtual_addr_base()
{
	if (!__HAS_INIT_IP)
	{
		init_cnn_accelerator();
	}
	return peripheral_virtual_addr_base;
}

bool close_cnn_accelerator()
{
	if (__HAS_INIT_IP == false)
	{
		/* nothing to do!! */
		return true;
	}
	__HAS_INIT_IP = false;
	if (munmap(peripheral_virtual_addr_base, HPS_H2F_LW_SPAN) != 0)
	{
		printf("ERROR: munmap() failed...\n");
		close(dev_mem_fd);
		return false;
	}
	close(dev_mem_fd);
	return true;
}

/* FILE operations below*/

static bool get_file_size(char *filename, uint32_t *file_size)
{
	struct stat statbuf;
	if (stat(filename, &statbuf) == -1)
	{
		printf("\n%s: file %s stat failed...\n", __FUNCTION__, filename);
		printf("Error: %s\n", strerror(errno));
		return false;
	}
	*file_size = statbuf.st_size;
	return true;
}

static bool file2buf(char *file_in, void *file_virtual_base, uint32_t file_size)
{
	int fd = open(file_in, O_RDONLY, S_IRWXU);

	if (fd == -1)
	{
		printf("%s:: open file failed!", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}

	char *buffer = (char *)malloc(sizeof(char) * file_size);
	if (buffer == NULL)
	{
		printf("%s:: malloc failed!", __FUNCTION__);
		close(fd);
		return false;
	}
	int len = 0;
	len = read(fd, buffer, file_size);
	if (len == -1)
	{
		printf("%s:: read file to buffer failed!", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd);
		free(buffer);
		return false;
	}
	memcpy(file_virtual_base, buffer, file_size);
	close(fd);
	free(buffer);
	return true;
}

bool buf2file(char *file_out, void *buffer, uint32_t size)
{
	int fd = open(file_out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		printf("%s:: open file failed!", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}
	int len = write(fd, buffer, size);
	if (len == -1)
	{
		printf("%s:: write buffer to file failed!", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd);
		return false;
	}
	close(fd);
	return true;
}

bool copy_file_to_ddr(char *filename, uint32_t hps_ddr_addr, uint32_t *size)
{
	if (hps_ddr_addr > HPS_DDR_ADDR_LIMIT)
	{
		printf("hps_ddr_addr (0x%x) should be <= 0x%x!\n", hps_ddr_addr, HPS_DDR_ADDR_LIMIT);
		return false;
	}
	void *file_virtual_base;
	unsigned int hps_ddr_span;
	int fd_mem;

	if (get_file_size(filename, &hps_ddr_span) == false)
	{
		return false;
	}
	if (hps_ddr_span > HPS_DDR_SPAN)
	{
		printf("%s:: the scale of file is too large! can't span too large!\n", __FUNCTION__);
		return false;
	}
	*size = hps_ddr_span;

#ifdef DEBUG_PRINT
	printf("%s::copy 0x%x bytes from %s to DDR at 0x%x\n", __FUNCTION__, hps_ddr_span, filename, hps_ddr_addr);
#endif

	// open virtual space.
	fd_mem = open("/dev/mem", (O_RDWR | O_SYNC));
	if ((fd_mem == -1))
	{
		printf("%s:: open /dev/mem failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}

#ifdef DEBUG_PRINT
	printf("%s:: mmap: len 0x%x offset: 0x%x\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr);
#endif
	if (hps_ddr_span == 0xC)
	{
		hps_ddr_span = 0x10;
		printf("%s:: len 0x%x changed to 16\n", __FUNCTION__, hps_ddr_span);
	}
	file_virtual_base = mmap(NULL, hps_ddr_span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd_mem, hps_ddr_addr);
	if (file_virtual_base == MAP_FAILED)
	{
		printf("\n%s: file_virtual_base mmap() failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd_mem);
		return false;
	}
	// copy data from file to ddr_kmem.
	bool rv = file2buf(filename, (void *)(file_virtual_base), hps_ddr_span);

	munmap(file_virtual_base, hps_ddr_span);
	close(fd_mem);

	return rv;
}

bool copy_mem_to_ddr(void *buffer_address, uint32_t hps_ddr_addr, uint32_t hps_ddr_span)
{
	if (hps_ddr_addr > HPS_DDR_ADDR_LIMIT)
	{
		printf("hps_ddr_addr (0x%x) should be <= 0x%x!\n", hps_ddr_addr, HPS_DDR_ADDR_LIMIT);
		return false;
	}
	void *file_virtual_base;
	int fd_mem;

	if (hps_ddr_span > HPS_DDR_SPAN)
	{
		printf("%s:: the scale of file is too large! can't span too large!\n", __FUNCTION__);
		return false;
	}

#ifdef DEBUG_PRINT
	printf("%s::copy 0x%x bytes from mem @0x%p to DDR at 0x%x\n", __FUNCTION__, hps_ddr_span, buffer_address, hps_ddr_addr);
#endif

	// open virtual space.
	fd_mem = open("/dev/mem", (O_RDWR | O_SYNC));
	if ((fd_mem == -1))
	{
		printf("%s:: open /dev/mem failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}

#ifdef DEBUG_PRINT
	printf("%s:: mmap: len 0x%x offset: 0x%x\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr);
#endif
	file_virtual_base = mmap(NULL, hps_ddr_span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd_mem, hps_ddr_addr);
	if (file_virtual_base == MAP_FAILED)
	{
		printf("\n%s: file_virtual_base mmap() failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd_mem);
		return false;
	}
	// copy data from mem to ddr_kmem.
	memcpy(file_virtual_base, buffer_address, hps_ddr_span);

	munmap(file_virtual_base, hps_ddr_span);
	close(fd_mem);
	return true;
}

bool read_file_from_ddr(char *filename, uint32_t hps_ddr_addr, uint32_t hps_ddr_span)
{
#ifdef DEBUG_PRINT
	printf("%s:: read 0x%x bytes from DDR at 0x%x to %s\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr, filename);
#endif

	if (hps_ddr_addr > HPS_DDR_ADDR_LIMIT)
	{
		printf("hps_ddr_addr (0x%x) should be <= 0x%x!\n", hps_ddr_addr, HPS_DDR_ADDR_LIMIT);
		return false;
	}
	// get span scale.
	if (hps_ddr_span > HPS_DDR_SPAN)
	{
		printf("%s:: the scale of file is too large! can't span too large!\n", __FUNCTION__);
		return false;
	}
	void *file_virtual_base;
	int fd_mem;
	// open virtual space.
	fd_mem = open("/dev/mem", (O_RDWR | O_SYNC));
	if ((fd_mem == -1))
	{
		printf("%s:: open /dev/mem failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}
	// map file's addr.
#ifdef DEBUG_PRINT
	printf("%s:: mmap: len 0x%x offset: 0x%x\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr);
#endif
	file_virtual_base = mmap(NULL, hps_ddr_span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd_mem, hps_ddr_addr);
	if (file_virtual_base == MAP_FAILED)
	{
		printf("%s:: file_virtual_base mmap() failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd_mem);
		return false;
	}
	// copy data from ddr_kmem to file.
	bool rv = buf2file(filename, (void *)(file_virtual_base), hps_ddr_span);
	// close mmap kmem.
	munmap(file_virtual_base, hps_ddr_span);
	close(fd_mem);

	return rv;
}

bool copy_ddr_to_mem(void *buffer_address, uint32_t hps_ddr_addr, uint32_t hps_ddr_span)
{
#ifdef DEBUG_PRINT
	printf("%s:: read 0x%x bytes from DDR at 0x%x to mem @0x%p\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr, buffer_address);
#endif
	if (hps_ddr_addr > HPS_DDR_ADDR_LIMIT)
	{
		printf("hps_ddr_addr (0x%x) should be <= 0x%x!\n", hps_ddr_addr, HPS_DDR_ADDR_LIMIT);
		return false;
	}
	// get span scale.
	if (hps_ddr_span > HPS_DDR_SPAN)
	{
		printf("%s:: the scale of file is too large! can't span too large!\n", __FUNCTION__);
		return false;
	}
	void *file_virtual_base;
	int fd_mem;
	// open virtual space.
	fd_mem = open("/dev/mem", (O_RDWR | O_SYNC));
	if ((fd_mem == -1))
	{
		printf("%s:: open /dev/mem failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		return false;
	}
	// map file's addr.
#ifdef DEBUG_PRINT
	printf("%s:: mmap: len 0x%x offset: 0x%x\n", __FUNCTION__, hps_ddr_span, hps_ddr_addr);
#endif
	file_virtual_base = mmap(NULL, hps_ddr_span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd_mem, hps_ddr_addr);
	if (file_virtual_base == MAP_FAILED)
	{
		printf("%s:: file_virtual_base mmap() failed...\n", __FUNCTION__);
		printf("Error: %s\n", strerror(errno));
		close(fd_mem);
		return false;
	}
	// copy data from ddr_kmem to kmem.
	memcpy(buffer_address, file_virtual_base, hps_ddr_span);

	// close mmap kmem.
	munmap(file_virtual_base, hps_ddr_span);
	close(fd_mem);
	return true;
}

bool bin2json(char *filename, int h, int w, int pad, uint8_t *img)
{
	//w: always create a new file
	FILE *fptr = fopen(filename, "w");

	if (fptr == NULL)
	{
		printf("%s:: fopen %s failed...\n", __FUNCTION__, filename);
		return false;
	}
	fprintf(fptr, "[\n");
	for (int hi = 0; hi < h; hi++)
	{ // 32 h
		if (hi != 0)
		{
			fprintf(fptr, "    ],\n");
		}
		fprintf(fptr, "    [\n");
		for (int wi = 0; wi < w; wi++)
		{ // 128 w
			if (wi != 0)
			{
				fprintf(fptr, "        ],\n");
			}
			fprintf(fptr, "        [\n");
			for (int k = 0; k < 3; k++)
			{
				if (k != 2)
					fprintf(fptr, "            %d,\n", (uint32_t) * (img + (hi * w + wi) * (3 + pad) + k));
				else
					fprintf(fptr, "            %d\n", (uint32_t) * (img + (hi * w + wi) * (3 + pad) + k));
			}
		}
		fprintf(fptr, "        ]\n");
	}
	fprintf(fptr, "    ]\n");
	fprintf(fptr, "]");

	return true;
}

bool bin2json2(char *filename, int h, int w, int pad, uint8_t *img)
{
	//w: always create a new file
	FILE *fptr = fopen(filename, "w");

	if (fptr == NULL)
	{
		printf("%s:: fopen %s failed...\n", __FUNCTION__, filename);
		return false;
	}
	fprintf(fptr, "[\n");
	for (int hi = 0; hi < h; hi++)
	{ // 32 h
		if (hi != 0)
		{
			fprintf(fptr, "    ],\n");
		}
		fprintf(fptr, "    [\n");
		for (int wi = 0; wi < w; wi++)
		{ // 128 w
			if (wi != 0)
			{
				fprintf(fptr, "        ],\n");
			}
			fprintf(fptr, "        [\n");
			for (int k = 0; k < 3; k++)
			{
				if (k != 2)
					fprintf(fptr, "            %d,\n", (uint32_t) * (img + k * h * w + hi * w + wi));
				else
					fprintf(fptr, "            %d\n", (uint32_t) * (img + k * h * w + hi * w + wi));
			}
		}
		fprintf(fptr, "        ]\n");
	}
	fprintf(fptr, "    ]\n");
	fprintf(fptr, "]");

	return true;
}
#if 0
//uint8_t fx_chunk_img[32][8][3];
//int trunk;
char filename[100];
for (int t = 0; t < 16; t++) { // 16

	//break whole pic into 8 trunks , each of 32x8x3
	trunk = t*8;
	for (int wi = 0; wi < 8; wi++) { // 8 w
		for (int hi = 0; hi < 32; hi++) { // 32 h
			for (int k = 0; k < 3; k++) {
				fx_chunk_img[hi][wi][k] = fx_resized_img[hi][trunk + wi][k];
				if (fx_chunk_img[hi][wi][k] != *(img_ptr + (hi*128 + (trunk + wi))*3 + k))
				{
					printf("no equal:: t: %d, wi: %d, hi: %d, k: %d\n", t, wi, hi, k);
				}
			}
		}
	}
#endif

//assemble 8 trunks , each of 32x8x3 to whole pic, 32x128x3, pad is for input file trunks
// void assemble_trunks_to_whole_picture(uint8_t *whole_picture, int pad, uint8_t *img_trunks_ptr[])
// {
// 	uint8_t *src_img;
// 	int trunk;
// 	for (int t = 0; t < 16; t++) { // 16
// 		src_img = img_trunks_ptr[t];
// 		trunk = t*8;
// 		for (int wi = 0; wi < 8; wi++) { // 8 w
// 			for (int hi = 0; hi < 32; hi++) { // 32 h
// 				for (int k = 0; k < 3; k++) {
// 					*(whole_picture + (hi*128 + (trunk + wi))*3 + k) = *(src_img + (hi*8 + wi)*(3+pad) + k);
// 				}
// 			}
// 		}
// 	}
// }

void assemble_trunks_to_whole_picture(uint8_t *whole_picture, int pad, uint8_t *img_trunks_ptr[])
{
	uint8_t *src_img;
	int trunk;
	for (int t = 0; t < 16; t++)
	{ // 16
		src_img = img_trunks_ptr[t];
		trunk = t * 8;
		for (int wi = 0; wi < 8; wi++)
		{ // 8 w
			for (int hi = 0; hi < 32; hi++)
			{ // 32 h
				for (int k = 0; k < 3; k++)
				{
					*(whole_picture + (hi * 128 + (trunk + wi)) * 3 + k) = *(src_img + k * 8 * 32 + hi * 8 + wi);
				}
			}
		}
	}
}
/*
 * compare two binary files character by character
 */
static char *cfile2buf(char *file_in)
{
	int fd = open(file_in, O_RDONLY, S_IRWXU);
	if (fd == -1)
	{
		printf("open file filed!");
		exit(0);
	}
	unsigned int size = 0;
	get_file_size(file_in, &size);
	char *buffer = (char *)malloc(sizeof(char) * size);
	int len = read(fd, buffer, size);
	if (len == -1)
	{
		printf("read file to buffer failed!");
		exit(0);
	}
	return buffer;
}

bool compare_files(char *f1, char *f2)
{
	// copy file to buffer.
	bool rv = true;
	char *buffer_1 = cfile2buf(f1);
	char *buffer_2 = cfile2buf(f2);
	unsigned int size_1 = 0, size_2 = 0;
	get_file_size(f1, &size_1);
	get_file_size(f2, &size_2);
	if (size_1 != size_2)
	{
		printf("%s:: the scale of two file is not match!!!\n", __FUNCTION__);
		return false;
	}
	int i;
	for (i = 0; i < size_1; ++i)
	{
		if (buffer_1[i] != buffer_2[i])
		{
			printf("%s:: mismatch at %d!!!\n", __FUNCTION__, i);
			rv = false;
			break;
		}
	}
	return rv;
}
