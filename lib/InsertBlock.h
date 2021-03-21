#ifndef InsertBlock_H
#define InsertBlock_H

template<typename SeqIt>
void insertBlock(SeqIt source, int m, int n,
  SeqIt target, int upper_margin, int left_margin, int right_margin)
{
  int n_target = left_margin + n + right_margin;
  auto target_it = target + upper_margin*n_target + left_margin;
  auto source_it = source;
  for (int j = 0; j < m; ++j)
  {
    for (int i = 0; i < n; ++i)
    {
      *(target_it + i) = *(source_it + i);
    }
    target_it += n_target;
    source_it += n;
  }
}

#endif /* end of include guard: InsertBlock_H */
