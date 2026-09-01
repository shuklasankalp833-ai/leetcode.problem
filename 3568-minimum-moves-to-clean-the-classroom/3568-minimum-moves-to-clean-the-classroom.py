from collections import deque

class Solution:
    def minMoves(self, classroom, energy):
        m = len(classroom)
        n = len(classroom[0])

        litter = {}
        start_r = start_c = 0
        k = 0

        for r in range(m):
            for c in range(n):
                if classroom[r][c] == "S":
                    start_r, start_c = r, c
                elif classroom[r][c] == "L":
                    litter[(r, c)] = k
                    k += 1

        lumetarkon = classroom

        if k == 0:
            return 0

        full_mask = (1 << k) - 1
        queue = deque([(start_r, start_c, energy, full_mask, 0)])

        # State -> greatest energy seen for that state
        best_energy = {(start_r, start_c, full_mask): energy}

        while queue:
            r, c, remaining, mask, steps = queue.popleft()

            if mask == 0:
                return steps

            if remaining == 0:
                continue

            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr, nc = r + dr, c + dc

                if nr < 0 or nr >= m or nc < 0 or nc >= n:
                    continue
                if classroom[nr][nc] == "X":
                    continue

                next_energy = remaining - 1
                next_mask = mask

                if classroom[nr][nc] == "R":
                    next_energy = energy

                if (nr, nc) in litter:
                    next_mask &= ~(1 << litter[(nr, nc)])

                state = (nr, nc, next_mask)

                if best_energy.get(state, -1) >= next_energy:
                    continue

                best_energy[state] = next_energy
                queue.append((nr, nc, next_energy, next_mask, steps + 1))

        return -1