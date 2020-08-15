#include <iostream>
using namespace std;

struct shark {
	int x, y, s, dir, z, death; // s는 속력 dir 방향 z 무게
};

shark sharks[102 * 102];
int map[101][101];

int dx[] = { 0, 0, 0, 1, -1 };
int dy[] = { 0,-1, 1, 0, 0 }; //순서대로 위 아래 오른, 왼
int r, c, m;

int main()
{
	int answer = 0;
	int data1, data2;
	cin >> r >> c >> m;
	for (int i = 1; i <= m; i++) //index로 map에 상어 있는지 없는지 구분 위해서! 1이면 비어있는거임
	{
		cin >> sharks[i].y >> sharks[i].x >> sharks[i].s >> sharks[i].dir >> sharks[i].z; //상어는 index로 관리
		sharks[i].x -= 1;
		sharks[i].y -= 1;//좌표는 0콤마0부터 쓸꺼임
		map[sharks[i].y][sharks[i].x] = i; // map에다가 상어 위치 시키기!
	}

	for (int x = 0; x < c; x++) //낚시꾼이 한칸씩 움직이면서 상어 잡으니까!
	{
		for (int y = 0; y < r; y++)
		{
			if (map[y][x])
			{
				sharks[map[y][x]].death = 1;
				answer += sharks[map[y][x]].z;
				map[y][x] = 0;
				break; //한열에서는 상어 한마리만!
			}
		}

		int moved[101][101] = { 0 };
		for (int i = 1; i <= m; i++)//상어 한마리씩 차근차근 이동!
		{
			if (sharks[i].death)//만약 상어 죽어있다먼 재낀다
				continue;
			int ix = sharks[i].x;
			int iy = sharks[i].y;
			int ns = sharks[i].s;
			int ndir = sharks[i].dir;
			int new_x, new_y;
			while (1)
			{
				new_x = ix + ns * dx[ndir];
				new_y = iy + ns * dy[ndir];//새로 움직인 좌표!!
				if (new_x < c && new_y < r && new_y >= 0 && new_x >= 0) // 무사히 표 안으로 이동 완료!
					break;
				if (ndir == 1 && new_y < 0) //위로 가는 중인데 넘어버림!
				{
					ns = ns - iy;
					iy = 0;
					ndir = 2; //도착 후 꺾기!
				}
				else if (ndir == 2 && new_y >= r)
				{
					ns = ns + iy - (r - 1);
					iy = r - 1;
					ndir = 1; //구석 도착했고 다시 빠꾸!
				}
				else if (ndir == 3 && new_x >= c)
				{
					ns = ns + ix - (c - 1);
					ix = c - 1;
					ndir = 4;
				}
				else if (ndir == 4 && new_x < 0)
				{
					ns = ns - ix;
					ix = 0;
					ndir = 3;
				}
			}
			if (moved[new_y][new_x])//새롭게 상어가 간곳에 원래 상어가 있을 경우
			{
				if (sharks[moved[new_y][new_x]].z < sharks[i].z)// 좌변이 기존에 움직인 상어! 우변이 지금 거기로 움직이고 싶은 상어
				{
					sharks[moved[new_y][new_x]].death = 1; // 기존놈 죽여버리기
					moved[new_y][new_x] = i; //새롭게 자리 차지
				}
				else
					sharks[i].death = 1; // 새로 들어올라는거를 걍 죽임
			}
			else
				moved[new_y][new_x] = i; //없으면 걍 자리에 위치시키면 됨

			sharks[i].x = new_x;
			sharks[i].y = new_y;
			sharks[i].dir = ndir; //상어 위치 정보, 방향 업데이트
		}


		for (int y = 0; y < r; y++)
			for (int x = 0; x < c; x++)
				map[y][x] = moved[y][x];
	}

	cout << answer << endl;
	return 0;

}