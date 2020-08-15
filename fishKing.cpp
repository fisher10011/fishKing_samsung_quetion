#include <iostream>
using namespace std;

struct shark {
	int x, y, s, dir, z, death; // s�� �ӷ� dir ���� z ����
};

shark sharks[102 * 102];
int map[101][101];

int dx[] = { 0, 0, 0, 1, -1 };
int dy[] = { 0,-1, 1, 0, 0 }; //������� �� �Ʒ� ����, ��
int r, c, m;

int main()
{
	int answer = 0;
	int data1, data2;
	cin >> r >> c >> m;
	for (int i = 1; i <= m; i++) //index�� map�� ��� �ִ��� ������ ���� ���ؼ�! 1�̸� ����ִ°���
	{
		cin >> sharks[i].y >> sharks[i].x >> sharks[i].s >> sharks[i].dir >> sharks[i].z; //���� index�� ����
		sharks[i].x -= 1;
		sharks[i].y -= 1;//��ǥ�� 0�޸�0���� ������
		map[sharks[i].y][sharks[i].x] = i; // map���ٰ� ��� ��ġ ��Ű��!
	}

	for (int x = 0; x < c; x++) //���ò��� ��ĭ�� �����̸鼭 ��� �����ϱ�!
	{
		for (int y = 0; y < r; y++)
		{
			if (map[y][x])
			{
				sharks[map[y][x]].death = 1;
				answer += sharks[map[y][x]].z;
				map[y][x] = 0;
				break; //�ѿ������� ��� �Ѹ�����!
			}
		}

		int moved[101][101] = { 0 };
		for (int i = 1; i <= m; i++)//��� �Ѹ����� �������� �̵�!
		{
			if (sharks[i].death)//���� ��� �׾��ִٸ� �糤��
				continue;
			int ix = sharks[i].x;
			int iy = sharks[i].y;
			int ns = sharks[i].s;
			int ndir = sharks[i].dir;
			int new_x, new_y;
			while (1)
			{
				new_x = ix + ns * dx[ndir];
				new_y = iy + ns * dy[ndir];//���� ������ ��ǥ!!
				if (new_x < c && new_y < r && new_y >= 0 && new_x >= 0) // ������ ǥ ������ �̵� �Ϸ�!
					break;
				if (ndir == 1 && new_y < 0) //���� ���� ���ε� �Ѿ����!
				{
					ns = ns - iy;
					iy = 0;
					ndir = 2; //���� �� ����!
				}
				else if (ndir == 2 && new_y >= r)
				{
					ns = ns + iy - (r - 1);
					iy = r - 1;
					ndir = 1; //���� �����߰� �ٽ� ����!
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
			if (moved[new_y][new_x])//���Ӱ� �� ������ ���� �� ���� ���
			{
				if (sharks[moved[new_y][new_x]].z < sharks[i].z)// �º��� ������ ������ ���! �캯�� ���� �ű�� �����̰� ���� ���
				{
					sharks[moved[new_y][new_x]].death = 1; // ������ �׿�������
					moved[new_y][new_x] = i; //���Ӱ� �ڸ� ����
				}
				else
					sharks[i].death = 1; // ���� ���ö�°Ÿ� �� ����
			}
			else
				moved[new_y][new_x] = i; //������ �� �ڸ��� ��ġ��Ű�� ��

			sharks[i].x = new_x;
			sharks[i].y = new_y;
			sharks[i].dir = ndir; //��� ��ġ ����, ���� ������Ʈ
		}


		for (int y = 0; y < r; y++)
			for (int x = 0; x < c; x++)
				map[y][x] = moved[y][x];
	}

	cout << answer << endl;
	return 0;

}