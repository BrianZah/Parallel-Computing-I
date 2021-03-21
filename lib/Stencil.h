#ifndef Stencil_H
#define Stencil_H

template<typename SeqIt, typename Var>
bool borderedStencil(int m, int n, int iter,
             bool upper_node, bool under_node, bool left_node, bool right_node,
             Var alpha, Var dt, Var h_2, SeqIt Field_old_begin, SeqIt Field_new_begin)
{
  if (dt > h_2 / alpha) return false;

  Var help = alpha*dt/h_2;
  auto old_it = Field_old_begin;
  auto new_it = Field_new_begin;
  for (int j = 1+iter*(!upper_node); j < m-1-iter*(!under_node); ++j)
  {
    for (int i = 1+iter*(!left_node); i < n-1-iter*(!right_node); ++i)
    {
      *(new_it + j*n + i) = *(old_it + j*n + i) + help
            * (   *(old_it + (j-1)*n + i) + *(old_it + (j+1)*n + i)
                + *(old_it + j*n + (i-1)) + *(old_it + j*n + (i+1))
                - *(old_it + j*n + i)*4
              );
    }
  }
  return true;
}


template<typename SeqIt, typename Var>
bool stencil(int m, int n, Var alpha, Var dt, Var h_2,
             SeqIt Field_old_begin, SeqIt Field_new_begin)
{
  if (dt > h_2 / alpha) return false;

  Var help = alpha*dt/h_2;
  auto old_it = Field_old_begin;
  auto new_it = Field_new_begin;
  for (int j = 1; j < m-1; j++)
  {
    for (int i = 1; i < n-1; i++)
    {
      *(new_it + j*n + i) = *(old_it + j*n + i) + help
            * (   *(old_it + (j-1)*n + i) + *(old_it + (j+1)*n + i)
                + *(old_it + j*n + (i-1)) + *(old_it + j*n + (i+1))
                - *(old_it + j*n + i)*4
              );
    }
  }
  return true;
}

#endif /* end of include guard: Stencil_H */
