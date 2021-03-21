#ifndef SortField_H
#define SortField_H

template<typename SeqIt>
void sortField(const int n, const SeqIt target,
         const int n_block, const SeqIt source, const int sqrt_num)
{
  auto firstTargetValue = target;
  auto target_it = firstTargetValue;
  auto source_it = source;
  for (int y = 0; y < sqrt_num; ++y)
  {
    for (int x = 0; x < sqrt_num; ++x)
    {
      target_it = target + x*n_block + y*sqrt_num*n_block*n_block;
      for (int j = 0; j < n_block; ++j)
      {
        for (int i = 0; i < n_block; ++i)
        {
          *(target_it+i) = *(source_it + i);
        }
        source_it += n_block;
        target_it += n;
      }
    }
  }
}

#endif /* end of include guard: SortField_H */
