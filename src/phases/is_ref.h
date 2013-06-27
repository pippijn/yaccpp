static bool
is_ref (char c1)
{
  switch (c1)
    {
    case '$':
    case '`':
    case '@':
    case '#':
      return true;
    default:
      return false;
    }
}
