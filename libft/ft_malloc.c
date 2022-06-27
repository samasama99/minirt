#include "libft.h"

t_list *get_heap(t_list **command)
{
  static t_list **heap;

  if (command)
    heap = command;
  return *heap;
}

void *ft_malloc(size_t size)
{
  static t_list *heap;
  void          *mem;

  if (heap == NULL)
    get_heap(&heap); 
  mem = (void *)malloc(size);
  if (mem == NULL) {
    perror("Error:");
    exit(1);
  }
  ft_lstadd_back(&heap, ft_lstnew(mem));
  return mem;
}

void ft_free(void)
{
  t_list *heap;
  t_list *next;

  heap = get_heap(NULL);
  while (heap)
  {
    free(heap->content);
    heap->content = NULL;
    next = heap->next;
    free(heap);
    heap = next;
  }
}

// int main()
// {
//   int *x = ft_malloc(sizeof(int) * 3);
//   x[0] = 10;
//   x[1] = 15;
//   x[2] = 20;
//   // print_tupil("test", point(x[0], x[1], x[2]));
//   x = ft_malloc(sizeof(int) * 2);
//   x[0] = 250;
//   x[1] = 255;
//   // print_tupil("test", point(x[0], x[1], 0));
//   ft_free();
//   system("leaks a.out");
// }
