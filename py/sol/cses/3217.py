#!/usr/bin/python


from collections import deque


def solve(A: list[list[int]], n: int) -> None:
    def move(p: tuple[int, int]) -> list[tuple[int, int]]:
        r: list[tuple[int, int]] = []
        if -1 < p[0] -1 < n and -1 < p[1] -2 < n: r.append((p[0]-1, p[1]-2)) 
        if -1 < p[0] -1 < n and -1 < p[1] +2 < n: r.append((p[0]-1, p[1]+2)) 
        if -1 < p[0] +1 < n and -1 < p[1] -2 < n: r.append((p[0]+1, p[1]-2)) 
        if -1 < p[0] +1 < n and -1 < p[1] +2 < n: r.append((p[0]+1, p[1]+2)) 

        if -1 < p[0] -2 < n and -1 < p[1] -1 < n: r.append((p[0]-2, p[1]-1)) 
        if -1 < p[0] -2 < n and -1 < p[1] +1 < n: r.append((p[0]-2, p[1]+1)) 
        if -1 < p[0] +2 < n and -1 < p[1] -1 < n: r.append((p[0]+2, p[1]-1)) 
        if -1 < p[0] +2 < n and -1 < p[1] +1 < n: r.append((p[0]+2, p[1]+1)) 

        return (r)

    q: deque[tuple[int, int]]= deque()
    q.append((0,0))

    while q:
        cur: tuple[int, int] = q.popleft()

        for e in move(cur):
            if A[e[0]][e[1]] == -1:
                A[e[0]][e[1]] = A[cur[0]][cur[1]] + 1
                q.append(e)


if __name__ == "__main__":
    n: int = int(input()) 
    A: list[list[int]] = [[-1 for _ in range(n)] for _ in range(n)]
    A[0][0] = 0

    solve(A, n)

    for r in A:
        print(r[0], end="")
        for i in range(1, n):
            print(f" {r[i]}", end="")
        print()
