#define ASSOOFS_MAGIC 0x20170509
#define ASSOOFS_DEFAULT_BLOCK_SIZE 4096
#define ASSOOFS_FILENAME_MAXLEN 255
#define ASSOOFS_START_INO 10
#define ASSOOFS_RESERVED_INODES 3 
#define ASSOOFS_LAST_RESERVED_BLOCK ASSOOFS_ROOTDIR_DATABLOCK_NUMBER
#define ASSOOFS_LAST_RESERVED_INODE ASSOOFS_INODESTORE_BLOCK_NUMBER
const int ASSOOFS_SUPERBLOCK_BLOCK_NUMBER = 0;
const int ASSOOFS_INODESTORE_BLOCK_NUMBER = 1;
const int ASSOOFS_ROOTDIR_DATABLOCK_NUMBER = 2;
const int ASSOOFS_ROOTDIR_INODE_NUMBER = 1;
const int ASSOOFS_MAX_FILESYSTEM_OBJECTS_SUPPORTED = 64;

//Contiene informacion sobre el superbloque
struct assoofs_super_block_info {
    uint64_t version;

    uint64_t magic;
    uint64_t block_size;  
//contador de inodos creados  
    uint64_t inodes_count;
//mapa de bits
    uint64_t free_blocks;
//No nos insteresa, solo es un relleno para que ocupe exactamente un bloque
    char padding[4056];
};

//se usa cuando trabajemos con directorios
struct assoofs_dir_record_entry {
    char filename[ASSOOFS_FILENAME_MAXLEN];
    uint64_t inode_no;
};

//informacion sobre mis inodos, no sobre los inodos en si
struct assoofs_inode_info {
    mode_t mode;
//numero de inodos
    uint64_t inode_no;
//bloque donde esta almanecenaod el fichero
    uint64_t data_block_number;
    union {
//si es un fichero cuando ocupa
        uint64_t file_size;
//si es un directorio cuantos ficheros tiene
        uint64_t dir_children_count;
    };
};
