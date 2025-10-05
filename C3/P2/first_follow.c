#include <stdio.h>
#include <string.h>

int n_prods;
char prods[50][50];
char firsts[26][50];
int is_first_done[26];
char follows[26][50];
int is_follow_done[26];

int first_index;
char curr_firsts[50];

int follow_index;
char curr_follows[50];

int is_terminal(char c) {
    if (c < 65 || c > 90)
        return 1;
    return 0;
}

void first(char nonterm) {
    first_index = 0;
    for (int pi = 0; pi < n_prods; pi++) {
        if (prods[pi][0] == nonterm) {
            int curr_prod_index = 2;
            int flag = 0;
            while (prods[pi][curr_prod_index] != '\0' && flag == 0) {
                flag = 1;
                if (is_terminal(prods[pi][curr_prod_index])) {
                    curr_firsts[first_index] = prods[pi][2];
                    first_index++;
                    break;
                }
                if (!is_first_done[prods[pi][curr_prod_index] - 65])
                    first(prods[pi][curr_prod_index]);
                int in = 0;
                while (firsts[prods[pi][curr_prod_index] - 65][in] != '\0') {
                    curr_firsts[first_index] = firsts[prods[pi][curr_prod_index] - 65][in];
                    if (firsts[prods[pi][curr_prod_index] - 65][in] == 'e') {
                        curr_prod_index++;
                        flag = 0;
                    }
                    first_index++;
                    in++;
                }
            }
        }
    }
    curr_firsts[first_index] = '\0';
    first_index++;
    strcpy(firsts[nonterm - 65], curr_firsts);
    is_first_done[nonterm - 65] = 1;
}

void follow(char nonterm) {
    follow_index = 0;
    if (nonterm == prods[0][0]) {
        curr_follows[follow_index] = '$';
        follow_index++;
    }
    for (int pj = 0; pj < n_prods; pj++) {
        int k = 2;
        int include_lhs_flag;
        while (prods[pj][k] != '\0') {
            include_lhs_flag = 0;
            if (prods[pj][k] == nonterm) {
                if (prods[pj][k + 1] != '\0') {
                    if (is_terminal(prods[pj][k + 1])) {
                        curr_follows[follow_index] = prods[pj][k + 1];
                        follow_index++;
                        break;
                    }
                    int in = 0;
                    while (firsts[prods[pj][k + 1] - 65][in] != '\0') {
                        if (firsts[prods[pj][k + 1] - 65][in] == 'e') {
                            include_lhs_flag = 1;
                            in++;
                            continue;
                        }
                        int temp_flag = 0;
                        for (int z = 0; z < follow_index; z++)
                            if (firsts[prods[pj][k + 1] - 65][in] == curr_follows[z]) {
                                temp_flag = 1;
                                in++;
                                break;
                            }
                        if (temp_flag)
                            continue;
                        curr_follows[follow_index] = firsts[prods[pj][k + 1] - 65][in];
                        follow_index++;
                        in++;
                    }
                }
                if (prods[pj][k + 1] == '\0' || include_lhs_flag == 1) {
                    if (prods[pj][0] != nonterm) {
                        if (!is_follow_done[prods[pj][0] - 65])
                            follow(prods[pj][0]);
                        int x = 0;
                        while (follows[prods[pj][0] - 65][x] != '\0') {
                            int temp_flag = 0;
                            for (int z = 0; z < follow_index; z++)
                                if (follows[prods[pj][0] - 65][x] == curr_follows[z]) {
                                    temp_flag = 1;
                                    x++;
                                    break;
                                }
                            if (temp_flag)
                                continue;
                            curr_follows[follow_index] = follows[prods[pj][0] - 65][x];
                            follow_index++;
                            x++;
                        }
                    }
                }
            }
            k++;
        }
    }
    curr_follows[follow_index] = '\0';
    follow_index++;
    strcpy(follows[nonterm - 65], curr_follows);
    is_follow_done[nonterm - 65] = 1;
}

int main() {
    printf("Enter the number of productions : ");
    scanf("%d", &n_prods);
    printf("Enter productions (%d): \n",n_prods);
    for (int prod_i = 0; prod_i < n_prods; prod_i++)
        scanf("%s", prods[prod_i]);
    for (int fi = 0; fi < 26; fi++)
        is_first_done[fi] = 0;
    for (int fpi = 0; fpi < n_prods; fpi++)
        if (is_first_done[prods[fpi][0] - 65] == 0)
            first(prods[fpi][0]);
    for (int fli = 0; fli < n_prods; fli++)
        if (is_follow_done[prods[fli][0] - 65] == 0)
            follow(prods[fli][0]);
    printf("Firsts:\n");
    for (int fi = 0; fi < 26; fi++)
        if (is_first_done[fi])
            printf("%c : %s\n", fi + 65, firsts[fi]);
    printf("Follows:\n");
    for (int fi = 0; fi < 26; fi++)
        if (is_follow_done[fi])
            printf("%c : %s\n", fi + 65, follows[fi]);
}
