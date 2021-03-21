#ifndef GetMargin_H
#define GetMargin_H

void getMargin(int x_pos, int y_pos, int sqrt_num, int g,
  int& upper_margin, int& under_margin, int& left_margin, int& right_margin)
{
  upper_margin = g;
  under_margin = g;
  left_margin = g;
  right_margin = g;

  if (0 == x_pos) left_margin = 0;
  if (sqrt_num-1 == x_pos) right_margin = 0;
  if (0 == y_pos) upper_margin = 0;
  if (sqrt_num-1 == y_pos) under_margin = 0;
}

#endif /* end of include guard: GetMargin_H */
