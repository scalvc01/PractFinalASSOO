#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO  */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/fs.h>           /* libfs stuff           */
//#include <asm/uaccess.h>        /* copy_to_user          */
#include <linux/buffer_head.h>  /* buffer_head           */
#include <linux/slab.h>         /* kmem_cache            */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sandra Calvo Casares");

static struct dentry *assoofs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data);
int assoofs_fill_super(struct super_block *sb, void *data, int silent);

static struct file_system_type assoofs_type = {
	.owner = THIS_MODULE,
	.name = "assoofs",
	.mount = assoofs_mount,
	.kill_sb = kill_litter_super,
};

assoofs init {
	register_filesystem(&assoofs_type);
}

assofs exit {
	unregister_filesystem(&assoofs_type);
}

int assofs_fill_super(struct super_block *sb, void *data, int silent) {
	printk(KERN_INFO "assoofs_fill_super request \n");

	struct buffer_head *bh;
	struct assoofs_super_block_info *assoofs_sb;

	bh = sb_read(sb, ASSOOFS_SUPERBLOCK_BLOCK_NUMBER);
	assoofs_sb = (struct assoofs_super_block_info *) bh->b_data;

	if(assoofs_sb->magic != ASSOOFS_MAGIC){
		printk(KERN_ERR "The filesystem is not ASSOOFS.");
		return -1;
	}

	if(assoofs_sb->block_size != ASSOOFS_DEFAULT_BLOCK_SIZE){
		printk(KERN_ERR "Non standar block size.");
		return -1;
	}

	sb->s_magic=ASSOOFS_MAGIC;
	sb->s_maxbytes=ASSOOFS_DEFAULT_BLOCK_SIZE;
	sb->s_op=assofs_sops;
	sb->s_fs_info=assoofs_sb;



}

static struc dentry *assoofs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data) {
	struct dentry *ret = mount_bdev(fs_type, flags, dev_name, data, assofs_fill_super);
}


module_init(init_hello);
module_exit(cleanup_hello);
