int main()
{
  int x = 10;
  int * const t = &x;
  *t = 10;
}
