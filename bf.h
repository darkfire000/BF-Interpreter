typedef unsigned int uint;

#define CELL_COUNT 64
#define COMMAND_COUNT 2048
#define LOOP_STACK_SIZE 64

struct CallLater;

typedef struct {
	char *pointer;
	char cells[CELL_COUNT];
} CellTable;

typedef struct CallLater* (*function)(struct CallLater *cl, CellTable *ct);

typedef struct CallLater {
	function Function;
	struct CallLater* next;
	struct CallLater* fail;
} CallLater;