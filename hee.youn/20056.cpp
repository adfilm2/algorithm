#include<iostream>
using namespace std;
#define MAX_FIREBALL 1000000
#define MAX_N 50
#define fi(i, a, b) for(register int i = a; i < b; i++)


short dirX[]{ -1, -1, 0, 1, 1, 1, 0, -1 };
short dirY[]{ 0, 1, 1, 1, 0, -1, -1, -1 };
struct FireBall {
	int r;
	int c;
	int m;
	int s;
	int d;
	int step;
	FireBall* prev;
	FireBall* next;
};
FireBall* fireball();
void pool_init();
int N, M, K;

void list_insert(FireBall* list, FireBall* fireball);
void list_remove(FireBall* fireball);

FireBall map[MAX_N][MAX_N];
int step;

void move(FireBall* fireball) {
	list_remove(fireball);
	fireball->r += dirX[fireball->d] * fireball->s;
	while (fireball->r < 0) fireball->r += N;
	fireball->r = fireball->r % N;
	fireball->c += dirY[fireball->d] * fireball->s;
	while (fireball->c < 0) fireball->c += N;
	fireball->c = fireball->c % N;
	fireball->step = step;
	list_insert(&map[fireball->r][fireball->c], fireball);
}

int dir1[]{ 0, 2, 4, 6 };
int dir2[]{ 1, 3, 5, 7 };
void collision(FireBall* point) {
	int r = point->next->r;
	int c = point->next->c;

	int count = 0;
	int totMass = 0;
	int totSpeed = 0;
	int odd = 0;
	int even = 0;
	for (register FireBall* head = point->next; head; ) {
		count++;
		totMass += head->m;
		totSpeed += head->s;
		if (head->d % 2 == 0) even++;
		else odd++;
		FireBall* _head = head;
		head = head->next;
		list_remove(_head);
	}

	fi(i, 0, 4) {
		FireBall* newFireBall = fireball();
		newFireBall->r = r;
		newFireBall->c = c;
		newFireBall->m = totMass / 5;
		newFireBall->s = totSpeed / count;
		newFireBall->d = (even == 0 || odd == 0) ? dir1[i] : dir2[i];
		if (newFireBall->m == 0) continue;
		list_insert(&map[r][c], newFireBall);
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	cin >> N >> M >> K;
	pool_init();
	step = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			map[i][j] = {i, j, -1, -1, -1};
		}
	}
	fi(i, 0, M) {
		FireBall* ret = fireball();
		cin >> ret->r >> ret->c >> ret->m >> ret->s >> ret->d;
		ret->r -= 1;
		ret->c -= 1;
		list_insert(&map[ret->r][ret->c], ret);
	}
	fi(i, 0, K) {
		step++;
		fi(r, 0, N) {
			fi(c, 0, N) {
				for (register FireBall* head = map[r][c].next; head; ) {
					FireBall* _next = head->next;
					if (head->step != step) {
						move(head);
					}
					head = _next;
				}
			}
		}
		fi(r, 0, N) {
			fi(c, 0, N) {
				if (!map[r][c].next || !map[r][c].next->next) continue;
				collision(&map[r][c]);
			}
		}
	}
	int sum = 0;
	fi(r, 0, N) {
		fi(c, 0, N) {
			for (register FireBall* head = map[r][c].next; head; head = head->next) {
				sum += head->m;
			}
		}
	}
	cout << sum;
	return 0;
}

FireBall pool[MAX_FIREBALL];
int pool_size;
void pool_init() {
	pool_size = 0;
}
FireBall* fireball() {
	FireBall* ret = &pool[pool_size++];
	return ret;
}

void list_insert(FireBall* list, FireBall* fireball) {
	fireball->next = list->next;
	if(list->next) list->next->prev = fireball;
	list->next = fireball;
	fireball->prev = list;
}
void list_remove(FireBall* fireball) {
	fireball->prev->next = fireball->next;
	if(fireball->next) fireball->next->prev = fireball->prev;
	fireball->prev = 0;
	fireball->next = 0;
}