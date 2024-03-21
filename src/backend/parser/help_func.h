
#include "../types.h"


// help func
// help func to compare_operant_prior
int prior(token *tk); 
// compare two operations priority
int compare_operat_prior(token *ltk, token *rtk);
//write given token to a token struct and shifts equation by given index
void operantshift(token *curr_token, char operation, size_t *num_tokens, size_t * curr_qeat_idx, size_t shift);
// check if char is a function
bool is_function(const char *src, const char *func_name, size_t *shift);
// convert string number to double in token
bool stod(const char *snum, double *num, size_t *curr_eq_idx);