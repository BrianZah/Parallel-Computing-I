#ifndef InitField_H
#define InitField_H

template<typename SeqIt>
void initField(SeqIt field_begin, int m, int n, int x_pos, int y_pos, int sqrt_num)
{
	SeqIt field_it = field_begin;
	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
    {
      *(field_it) = 0.0;
      ++field_it;
    }
	}

	if (0 == x_pos)
  {
    field_it = field_begin;
    for (int j = 0; j < m; j++)
    {
      *(field_it) = 25.0;
      field_it += n;
    }
  }

	if (sqrt_num-1 == x_pos)
  {
    field_it = field_begin + n-1;
    for (int j = 0; j < m; j++)
    {
      *(field_it) = -25.0;
      field_it += n;
    }
  }

	if (0 == y_pos)
	{
    field_it = field_begin;
    for (int i = 0; i < n; i++)
    {
			*(field_it) = 25.0;
      ++field_it;
    }
	}

	if (sqrt_num-1 == y_pos)
	{
		field_it = field_begin + n*(m-1);
    for (int i = 0; i < n; i++)
    {
			 *(field_it) = -25.0;
       ++field_it;
     }
	}

}

#endif /* end of include guard: InitField_H */
