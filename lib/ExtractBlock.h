#ifndef ExtractBlock_H
#define ExtractBlock_H

template<typename SeqIt>
void extractBlock(SeqIt source, int upper_margin, int left_margin, int right_margin,
  SeqIt target, int m, int n)
{
  int n_source = left_margin + n + right_margin;
  auto target_it = target;
  auto source_it = source + upper_margin*n_source + left_margin;
  for (int j = 0; j < m; ++j)
  {
    for (int i = 0; i < n; ++i)
    {
      *(target_it + i) = *(source_it + i);
    }
    target_it += n;
    source_it += n_source;
  }
}

#endif /* end of include guard: ExtractBlock_H */
