queue = []
dir_list = [(-1, 0), (1, 0), (0, -1), (0, 1)]

def solution(maps):
    n = len(maps)
    m = len(maps[0])
    visit = [ [0] * m for _ in range(n)]
    queue.append((0,0))
    visit[0][0] = 1
    while len(queue) > 0:
        cur = queue.pop(0)
        if cur[0] == n - 1 and cur[1] == m - 1:
            break
        for dir in dir_list:
            [r, c] = map(lambda x: cur[x] + dir[x], range(2))
            if r not in range(n) or c not in range(m):
                continue
            if maps[r][c] == 0:
                continue
            if visit[r][c] > 0:
                continue
            visit[r][c] = visit[cur[0]][cur[1]] + 1
            queue.append((r, c))
    answer = visit[n - 1][m - 1]
    if answer == 0:
        return -1
    return answer
