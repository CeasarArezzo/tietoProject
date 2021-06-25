#include <circular_buffer.h>
#include <assert.h>

struct circular_buf_t {
	char ** buffer;
	size_t head;
	size_t tail;
	size_t capacity;
	bool full;
};

static void insert_move(cbuf_handle_t cbuf);
static void pop_move(cbuf_handle_t cbuf);

cbuf_handle_t circular_buf_init(size_t size)
{
    if (size)
    {
        cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
        if (cbuf)
        {
            cbuf->buffer = malloc(size * sizeof(char*));
            cbuf->head = 0;
            cbuf->tail = 0;
            cbuf->full = false;
	        cbuf->capacity = size;
        }
    }
    return NULL;
}

static void insert_move(cbuf_handle_t cbuf)
{
	assert(cbuf);

    cbuf->head = (cbuf->head + 1) % cbuf->capacity;
    if(circular_buf_full(cbuf))
    {
        cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
    }
    else
    {
        cbuf->full = (cbuf->head == cbuf->tail);
    }
}

static void pop_move(cbuf_handle_t cbuf)
{
	assert(cbuf);

	cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
}