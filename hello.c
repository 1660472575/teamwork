#include <stdio.h>

void main()
{
   printf("Hello world");

   register_chrdev_region(dev_t, unsigned, const char *)
   	alloc_chrdev_region(dev_t * dev, unsigned baseminor, unsigned count, const char * name)
   	kmalloc(size_t size, gfp_t flags)
   	kfree(ops)

   buffer.c
   get_hash(struct hda_cache_rec * cache, u32 key)

   block2mtd_write(struct mtd_info * mtd, loff_t to, size_t len, size_t * retlen, const u_char * buf)

   COPY(a, b, n)

   __bread(struct block_device * bdev, sector_t block, unsigned size)


	super_block

   CLEAR_BLOCK

   clear_bl_bit(void)

   find_first_zero_bit(p, sz)
   free_block(struct kmem_cache * cachep, void * * objpp, int len, int node)

   get_super(struct block_device *)

	get_hash_bucket(struct dma_debug_entry * entry, unsigned long * flags)
	init_block
	   bmap(struct inode *, sector_t)
	   get_pipe_inode(void)
	__iget(struct inode * inode)
   __iput()
   
}
