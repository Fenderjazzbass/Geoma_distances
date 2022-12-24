#include <bits/stdc++.h>
using namespace std;

struct point{
  double x;
  double y;
  void setvector(point a, point b){ //иногда мы захотим делать вектора на структуре point 
    x = b.x - a.x;
    y = b.y - a.y;
}
};
//векторное произведение мастхэв
double vec_pr(point a, point b){
  return a.x*b.y - a.y*b.x;
}
//на четвёртом пункте я понял, что надо сделать скалярное произведение
double scalar(point a, point b){
  return a.x*b.x + a.y*b.y;
}
//от точки до точки
double point_to_point(point first, point second){
  return sqrt((first.x-second.x)*(first.x-second.x) + (first.y - second.y)*(first.y - second.y)); //Пифагор 
}
//от точки до прямой
double point_to_line(point p, point a, point b){
  double dy = a.y - b.y; // -dy - иксовая координата нормали
  double dx = a.x - b.x; // dx - игрековая координата нормали
  double c = dy * a.x - dx * a.y;
  return abs((-dy * p.x + dx * p.y + c)/sqrt(dy*dy+dx*dx)); //формула расстояние от точки до прямой
}
//от точки до отрезка
double point_to_segment(point p, point a, point b) {
  //не всегда равно перпендикуляру, может быть равно расстоянию до ближайшего конца
  double dy = a.y - b.y; // -dy - иксовая координата нормали
  double dx = a.x - b.x; // dx - игрековая координата нормали
  point pa; // хотим вектора в координатах, почему бы не сделать вектор на пойнте?
  point pb; 
  point n;
  n.x = -dy;
  n.y = dx;
  pa.setvector(p, a);
  pb.setvector(p, b);
  //если вектор нормали находится между векторами pa и pb, то векторные произведения будут иметь разный знак
  if (vec_pr(n, pa) * vec_pr(n, pb) < 0)
    return point_to_line(p, a, b);
  else
    return min(point_to_point(p, a), point_to_point(p, b));
}
//от точки до луча (и тут становится больно)
double point_to_ray(point p, point a, point b){
  // будем понимать взаимное расположение луча и точки через косинус угла pab
  point ap;
  point ab;
  ap.setvector(a, p);
  ab.setvector(a, b);
  double check = scalar(ap, ab);
  if (check > 0)
    return point_to_line(p, a, b);
  else
    return point_to_point(p, a);
}


int main() {
  point A, B, C, D;
  cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y>>D.x>>D.y;
  //пункт 1 - расстояние от А до С
  cout<<point_to_point(A, C)<<'\n';
  //пункт 2 от точки A до отрезка CD
  cout<<point_to_segment(A, C, D)<<'\n';
  //пункт 3 от точки A до луча CD
  cout<<point_to_ray(A, C, D)<<'\n';
  //пункт 4 от точки A до прямой CD
  cout<<point_to_line(A, C, D)<<'\n';
  //имеет смысл определить вектора AB и CD
  point ab, cd;
  ab.setvector(A, B);
  cd.setvector(C, D);
  //пункт 5 от отрезка AB до точки C, серьёзно?
  cout<<point_to_segment(C, A, B)<<'\n';
  //пункт 6 от отрезка AB до отрезка CD
  //пункт 7 от отрезка AB до луча CD
  //пункт 8 от отрезка AB до прямой CD
  //пункт 9 от луча AB до точки C
  cout<<point_to_ray(C, A, B)<<'\n';
  //пункт 10 от луча AB до отрезка CD
  //пункт 11 от луча AB до луча CD
  //пункт 12 от луча AB до прямой CD
  //пункт 13 от прямой AB до точки C
  cout<<point_to_line(C, A, B)<<'\n';
  //пункт 14 от прямой AB до отрезка CD
  //пункт 15 от прямой AB до луча CD
  //тут три случая: параллельны, пересекаются, луч направлен в другую сторону
  if (abs(scalar(ab, cd)) == 1)
    cout<<point_to_line(A, C, D);
  else {} //тут будут непараллельные случаи
  //пункт 16 от прямой AB до прямой CD
  //самое простое - если параллельны, то считаем как от точки до прямой, иначе 0
  if (abs(scalar(ab, cd)) == 1)
    cout<<point_to_line(A, C, D);
  else
    cout<<0;
  
}