#!/usr/bin/python

import math

class Solution:
    def longestValidParentheses(self, s: str) -> int:
        c: int = 0
        res: int = 0

        def subPar(i: int, c:int) -> int:
            last_zero = i
            if c > 0: 
                c -= 1
                return c

            if s[i] == ")":
                return 0
            else:
                cond: int = 1
                j: int = i+1
                
                while j < len(s) and cond > -1:
                    if s[j] == "(": #)
                        cond += 1
                    else:
                        cond -= 1

                    if cond == 0:
                        last_zero = j
                    if cond > -1:
                        j += 1
                
                if last_zero == i:
                    return 0
                return last_zero-i + 1

        for i, e in enumerate(s):
            c = subPar(i, c)
            res = max(c, res)

        return res

                        

if __name__ == "__main__":
    S: Solution = Solution()
    s: str =")()())"
    r = S.longestValidParentheses(s)
    print(r)
    
