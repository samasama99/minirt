void repeat(int times, void (func)(), void *data)
{
  if (times == 0)
    return 
  func(data); 
  return repeat(times - 1, func, data);;
}
