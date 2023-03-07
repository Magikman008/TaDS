#ifndef COLORS_H
#define COLORS_H

#define res "\033[0m"
#define red "\033[31m"
#define gr "\033[32m"
#define yel "\033[33m"
#define blue "\033[34m"
#define cy "\033[36m"

#define del "\33[2K\033[A\r\33[2K"

#define MENU yel "Common tree\n" res gr                               \
                 "1. " res " Show tree\n" gr                          \
                 "2. " res " Add element to tree\n" gr                \
                 "3. " res " Search element in tree\n" gr             \
                 "4. " res " Search element in file\n" gr             \
                 "5. " res " Remove element from tree\n" yel          \
                 "Balanced tree\n" gr                                 \
                 "6. " res " Rebalance tree\n" gr                     \
                 "7. " res " Show tree\n" gr                          \
                 "8. " res " Search element in tree\n" gr             \
                 "9. " res " Remove element from tree\n" yel          \
                 "Open hash table\n" gr                               \
                 "10. " res "Show table\n" gr                         \
                 "11. " res "Search element in table\n" gr            \
                 "12. " res "Remove element from table\n" gr          \
                 "19. " res "Add element in table\n" yel              \
                 "Closed hash table\n" gr                             \
                 "13. " res "Show table\n" gr                         \
                 "14. " res "Search element in table\n" gr            \
                 "15. " res "Remove element from table\n" gr         \
                 "20. " res "Add element in table\n" yel              \
                 "Misc\n" gr                                          \
                 "16. " res "Add element to all structeres\n" gr      \
                 "17. " res "Delete element from all structeres\n" gr \
                 "18. " res "Update all structures from file\n" gr    \
                 "0. " res " Leave program\n" gr

#endif
