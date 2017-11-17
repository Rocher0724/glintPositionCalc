#include <iostream>
#include <cmath>
#include <spqr.hpp>
#include <vector>

using namespace std;

bool isInRect(int* rect) {

  float rectangleArea;
  int firstTriangle[3];
  firstTriangle[0] = rect[0];
  firstTriangle[1] = rect[1];
  firstTriangle[2] = rect[2];

  cout << firstTriangle[0] << endl;
  cout << firstTriangle[1] << endl;
  cout << firstTriangle[2] << endl;
  return false;
}

struct glintInfo {
  int x;
  int y;
  int number;
  bool isAppear;
};

void setResult(vector<glintInfo> &result, int x, int y, int num) {
  if (result[num-1].number == -1) {
    result[num-1] = {x, y, num, true};
  }
}

struct point {
  int x;
  int y;
};

float sqrt(point a, point b) {
//  return sqrtf((p1x-p2x)*(p1x-p2x) + (p1y-p2y)*(p1y-p2y))
  return sqrtf((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

//
//         (1) *
//    (2)  *       * (6)
//
//    (3)  *       * (5)
//        (4)  *
//
//  Glint 가 있을때 점 번호는 위와같이 정한다.
int main() {


  point p1 = {360, 300};
  point p2 = {326, 284};
  point p3 = {321, 246};
  point p4 = {357, 224};
  point p5 = {391, 245};
  point p6 = {390, 285};

  //todo  2,3,5,6 일때 틀림 틀리는경우가 한두개가아님.
  vector<point> qqq;
//  qqq.push_back(p1);
  qqq.push_back(p2);
  qqq.push_back(p3);
//  qqq.push_back(p4);
  qqq.push_back(p5);
  qqq.push_back(p6);

  glintInfo pp = {0, 0, -1, false};

  vector<glintInfo> result;
  result.push_back(pp);
  result.push_back(pp);
  result.push_back(pp);
  result.push_back(pp);
  result.push_back(pp);
  result.push_back(pp);



  int top_y = 0;
  int bottom_y = 1000;
  for (int i = 0; i < qqq.size(); ++i) {
    int temp_y = qqq[i].y;
    if (top_y < temp_y) {
      top_y = temp_y;
    }
    if (bottom_y > temp_y) {
      bottom_y = temp_y;
    }
  }
//  cout << "데헷 " << endl;

  for (int i = 0; i < qqq.size(); ++i) {
    int temp_x = qqq[i].x;
    int temp_y = qqq[i].y;
    if (top_y == temp_y) {
      for (int j = 0; j < qqq.size(); ++j) {
        if (i != j) {
          int temp2_y = qqq[j].y;
          int temp2_x = qqq[j].x;
          if (temp_y < temp2_y + 6 &&
              temp_y > temp2_y - 6) {

            // 여기 해당되면 2, 6번 세트이거나 , 3, 5번 세트이다
            if (temp_x > temp2_x) {
              // [i] 는 5번 혹은 6번
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x < temp3_x + 6 &&
                      temp_x > temp3_x - 6) {
                    if (temp_y > temp3_y) {
                      // [i]는 6번
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 5);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 5번점" << temp3_x << " " << temp3_y << endl;//                      i는 6번
                    } else {
                      // [i]는 5번 일수가없는게 6번이 없으면 여기에 해당될 수가 없다.
                      cout << "5번 ? " << temp_x << " " << temp_y << endl;
                    }

                  } else {
//                    cout << "i ? " << i << endl;
                    // 5번이나 6번인데 5번이면 6번점이 현재 없고 6번이면 5번점이 현재없다.

                    // 현재까지 찾아낸 경우
                    // 3,4,5번점만 있는데 5번점의 y값이 3번 점보다 클때,
                    // 1번점이없고 2,6번점이 있는데 6번점의 y값이 2번점의 y값보다 클때



                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 > distance002 - 6 &&
                        distance001 < distance002 + 6) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 < distance002 - 6) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 3);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 3번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 > distance002 + 6) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            } else {

              // [i] 는 2번 혹은 3번
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x < temp3_x + 6 &&
                      temp_x > temp3_x - 6) {
                    if (temp_y > temp3_y) {
                      // [i]는 2번점
                      setResult(result, temp_x, temp_y, 2);
                      setResult(result, temp2_x, temp2_y, 6);
                      setResult(result, temp3_x, temp3_y, 3);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 3번점" << temp3_x << " " << temp3_y << endl;

                      // todo i j k 외에 점이 더 있다면 4번 5번도 판별이 가능할것으로 보인다.

                    } else {
                      // [i]는 3번... 일수가 없다. 2번이없으면 3번이 여기에 올수 없기때문.
                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
                      cout << "3번 판별완료  " << endl;
                    }

                  } else {
                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 > distance002 - 6 &&
                        distance001 < distance002 + 6) {
                      setResult(result, temp_x, temp_y, 2);
                      setResult(result, temp2_x, temp2_y, 6);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 < distance002 - 6) {
                      setResult(result, temp_x, temp_y, 2);
                      setResult(result, temp2_x, temp2_y, 6);
                      setResult(result, temp3_x, temp3_y, 5);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 5번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 > distance002 + 6) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            }
            // 1번이거나 수평한 점이 안나타났거나
          } else if(temp_x < temp2_x + 6 &&
                    temp_x > temp2_x - 6) {
            if (temp_y > temp2_y && sqrt(qqq[i], qqq[j]) > 60) {
              setResult(result, temp_x, temp_y, 1);
//              cout << "i는 1번점" << temp_x << " " << temp_y << endl;
              // TODO i번 빼고 나머지 넣으면 2,3,4,5,6 판별될거같은데?
            } else {
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x > temp3_x + 10) {

                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 + 6 < distance002 &&
                        distance001* 1.73 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 * 1.73 + 6 < distance002 &&
                               distance001 * 2 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 3);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 3번점" << temp3_x << " " << temp3_y << endl;
                    }
                  } else if (temp_x < temp3_x - 10) {
                    // i는 2번점 j는 3번  k는 4번 혹은 5번점
                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 + 6 < distance002 &&
                        distance001* 1.73 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 2);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 4);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 4번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 * 1.73 + 6 < distance002 &&
                        distance001 * 2 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 2);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 5);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 5번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            }
          }
        } else {
          // i = j인 경우는 나올수밖에 없다
        }
      }
    }

    // 아래점부터 계산하는 로직을 똑같이 짜면 더 많은 점에 대한 경우를 알수있지 않을까?
    if (bottom_y == temp_y) {
      for (int j = 0; j < qqq.size(); ++j) {
        if (i != j) {
          int temp2_y = qqq[j].y;
          int temp2_x = qqq[j].x;
          if (temp_y < temp2_y + 6 &&
              temp_y > temp2_y - 6) {
//            cout << "i : " << i << endl;
//            cout << "j : " << j << endl;

            // 여기 해당되면 2, 6번 세트이거나 , 3, 5번 세트이다
            if (temp_x > temp2_x) {
              // [i] 는 5번 혹은 6번
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x < temp3_x + 6 &&
                      temp_x > temp3_x - 6) {
                    if (temp_y < temp3_y) {
                      // [i]는 5번
                      setResult(result, temp_x, temp_y, 5);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 6);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 6번점" << temp3_x << " " << temp3_y << endl;//                      i는 6번
                    } else {
                      // [i]는 6번 일수가없는게 6번이 없으면 여기에 해당될 수가 없다.
                      cout << "5번 ? " << temp_x << " " << temp_y << endl;
                    }

                  } else {
//                    cout << "i ? " << i << endl;
                    // 5번이나 6번인데 5번이면 6번점이 현재 없고 6번이면 5번점이 현재없다.

                    // 현재까지 찾아낸 경우
                    // 3,4,5번점만 있는데 5번점의 y값이 3번 점보다 클때,
                    // 1번점이없고 2,6번점이 있는데 6번점의 y값이 2번점의 y값보다 클때



                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 > distance002 - 6 &&
                        distance001 < distance002 + 6) {
                      setResult(result, temp_x, temp_y, 5);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 1);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 < distance002 - 6) {
                      setResult(result, temp_x, temp_y, 5);
                      setResult(result, temp2_x, temp2_y, 3);
                      setResult(result, temp3_x, temp3_y, 2);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 3번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 2번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 > distance002 + 6) {
                      setResult(result, temp_x, temp_y, 6);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 1);
//                      cout << "i는 6번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            } else {

              // [i] 는 2번 혹은 3번
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x < temp3_x + 6 &&
                      temp_x > temp3_x - 6) {
                    if (temp_y < temp3_y) {
                      // [i]는 3번점
                      result[2] = {temp_x, temp_y, 3, true};
                      result[4] = {temp2_x, temp2_y, 5, true};
                      result[3] = {temp3_x, temp3_y, 2, true};
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 2번점" << temp3_x << " " << temp3_y << endl;

                      // todo i j k 외에 점이 더 있다면 4번 5번도 판별이 가능할것으로 보인다.

                    } else {
                      // [i]는 3번... 일수가 없다. 2번이없으면 3번이 여기에 올수 없기때문.
                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
                      cout << "3번 판별완료  " << endl;
                    }

                  } else {
                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 > distance002 - 6 &&
                        distance001 < distance002 + 6) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 1);
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 < distance002 - 6) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 6);
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 5번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 6번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 > distance002 + 6) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 5);
                      setResult(result, temp3_x, temp3_y, 2);
//                      cout << "i는 2번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            }
            // 4번이거나 수평한 점이 안나타났거나
            // i는 3번 또는 5번
          } else if(temp_x < temp2_x + 6 &&
                    temp_x > temp2_x - 6) {
            if (temp_y < temp2_y && sqrt(qqq[i], qqq[j]) > 60) {
              setResult(result, temp_x, temp_y, 4);
//              cout << "i는 4번점" << temp_x << " " << temp_y << endl;
              // TODO i번 빼고 나머지 넣으면 1,2,3,5,6 판별될거같은데?
            } else {
              for (int k = 0; k < qqq.size(); ++k) {
                if (k != i && k != j) {
                  int temp3_y = qqq[k].y;
                  int temp3_x = qqq[k].x;
                  if (temp_x > temp3_x + 10) {
// i는 5
                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 + 6 < distance002 &&
                        distance001* 1.73 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 5);
                      setResult(result, temp2_x, temp2_y, 6);
                      setResult(result, temp3_x, temp3_y, 1);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 * 1.73 + 6 < distance002 &&
                        distance001 * 2 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 5);
                      setResult(result, temp2_x, temp2_y, 6);
                      setResult(result, temp3_x, temp3_y, 2);
//                      cout << "i는 5번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 6번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 2번점" << temp3_x << " " << temp3_y << endl;
                    }
                  } else if (temp_x < temp3_x - 10) {
                    // i는 3번점 j는 2번  k는 1번 혹은 6번점
                    float distance001 = sqrt(qqq[i], qqq[j]);
                    float distance002 = sqrt(qqq[i], qqq[k]);
//                    cout << "dis001 : " << distance001 << endl;
//                    cout << "dis002 : " << distance002 << endl;

                    if (distance001 + 6 < distance002 &&
                        distance001* 1.73 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 1);
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 1번점" << temp3_x << " " << temp3_y << endl;
                    } else if (distance001 * 1.73 + 6 < distance002 &&
                        distance001 * 2 + 6 > distance002) {
                      setResult(result, temp_x, temp_y, 3);
                      setResult(result, temp2_x, temp2_y, 2);
                      setResult(result, temp3_x, temp3_y, 6);
//                      cout << "i는 3번점" << temp_x << " " << temp_y << endl;
//                      cout << "j는 2번점" << temp2_x << " " << temp2_y << endl;
//                      cout << "k는 6번점" << temp3_x << " " << temp3_y << endl;
                    }
                  }
                }
              }
            }
          }
        } else {
          // i = j인 경우는 나올수밖에 없다.
        }
      }
    }
  }




  for (auto a : result) {
    cout <<" " << a.number << " " << a.x << " " << a.y << " " << a.isAppear << endl;
  }



  return 0;
}
