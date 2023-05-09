1. map -> Set would be masked map. set of pairs. sorting set based on 1 element of a pair at first. class stored in set.
1. dates are key and then store a value then lookup according to date
2. stack
ex01 line 102 + line 103 RPN.cpp for ./RPN "8 4 + 1 2 3 - -" WRONG.
this needs to be ./RPN "8 4 + 1 2 3 - - -" 
3. vector + list -> vector => random access iterators deque > list because iterators are the same.
4. for bigger list takes more time and for smaller vector less time. key is insertion and removal of elements

- ex00
  - req for parsing: 
    - must find "date | value" or "Year-Month-Day | 0-1000"
  - Condition Flow:
    - Check for exact match of "date | value"
    - Check Date Format -> YYYY-MM-DD where Month must be between 1 - 12 and DD between 1 and 31 Year YYYY 2009 or more. if less than 2009 = predates exchange.
    - Check value => convert to float and check between 0 - 1000.
    - find date in data.csv -> if match => conversion to value then output
      - if NO match => nearest (lower) date OR
      - Predates exchange OR
      - exceeds exchange


- TDD(trial)
  - 0: emptytest.txt
  - 1: dataValueonly.txt
  - 2: leaptest.txt => Leap year Test
  - 3: subjectInput.txt
  - 4: valuetest.txt => value, random_empty_spaces, pipe_only_no_right_side
  - 5: precede date
  - 6: exceed date