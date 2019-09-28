/*******************************************************/
/**  Autogenerated cart trees for us_nums    */
/*******************************************************/

#include "us_nums_cart.hpp"

#include "flite/regex/regex.hpp"
#include "flite/stats/cart.hpp"
#include "flite/utils/string.hpp"

extern const cst_cart us_nums_cart;

static const cst_cart_node us_nums_cart_nodes[] = {
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0000, (cst_val*)&val_0000},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0001, (cst_val*)&val_0001},
    {2, CST_CART_OP_IS, CTNODE_us_nums_NO_0002, (cst_val*)&val_0002},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0004},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0005, (cst_val*)&val_0001},
    {2, CST_CART_OP_IS, CTNODE_us_nums_NO_0006, (cst_val*)&val_0002},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0004},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0009, (cst_val*)&val_0006},
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0010, (cst_val*)&val_0007},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0011, (cst_val*)&val_0006},
    {4, CST_CART_OP_IS, CTNODE_us_nums_NO_0012, (cst_val*)&val_0008},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {5, CST_CART_OP_IS, CTNODE_us_nums_NO_0016, (cst_val*)&val_0008},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0019, (cst_val*)&val_0007},
    {5, CST_CART_OP_IS, CTNODE_us_nums_NO_0020, (cst_val*)&val_0006},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0021, (cst_val*)&val_0008},
    {2, CST_CART_OP_IS, CTNODE_us_nums_NO_0022, (cst_val*)&val_0002},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0027, (cst_val*)&val_0010},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0028, (cst_val*)&val_0011},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0030, (cst_val*)&val_0008},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0031, (cst_val*)&val_0008},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0035, (cst_val*)&val_0012},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0037, (cst_val*)&val_0008},
    {5, CST_CART_OP_IS, CTNODE_us_nums_NO_0038, (cst_val*)&val_0008},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0039, (cst_val*)&val_0013},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0043, (cst_val*)&val_0014},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0045, (cst_val*)&val_0015},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0046, (cst_val*)&val_0016},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0049, (cst_val*)&val_0017},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0051, (cst_val*)&val_0018},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0052, (cst_val*)&val_0019},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0056, (cst_val*)&val_0006},
    {4, CST_CART_OP_IS, CTNODE_us_nums_NO_0057, (cst_val*)&val_0001},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {5, CST_CART_OP_IS, CTNODE_us_nums_NO_0059, (cst_val*)&val_0006},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {5, CST_CART_OP_IS, CTNODE_us_nums_NO_0062, (cst_val*)&val_0006},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0063, (cst_val*)&val_0001},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0065, (cst_val*)&val_0006},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0067, (cst_val*)&val_0019},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0070, (cst_val*)&val_0019},
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0071, (cst_val*)&val_0020},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0072, (cst_val*)&val_0021},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0073, (cst_val*)&val_0022},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {4, CST_CART_OP_IS, CTNODE_us_nums_NO_0077, (cst_val*)&val_0019},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {3, CST_CART_OP_IS, CTNODE_us_nums_NO_0080, (cst_val*)&val_0023},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {1, CST_CART_OP_IS, CTNODE_us_nums_NO_0082, (cst_val*)&val_0008},
    {4, CST_CART_OP_IS, CTNODE_us_nums_NO_0083, (cst_val*)&val_0008},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0085, (cst_val*)&val_0024},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0009},
    {0, CST_CART_OP_LESS, CTNODE_us_nums_NO_0088, (cst_val*)&val_0025},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0089, (cst_val*)&val_0026},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0090, (cst_val*)&val_0027},
    {6, CST_CART_OP_LESS, CTNODE_us_nums_NO_0091, (cst_val*)&val_0028},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0003},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, (cst_val*)&val_0005},
    {255, CST_CART_OP_NONE, 0, 0}};

static const char* const us_nums_feat_table[] = {
    "num_digits",
    "p.token_pos_guess",
    "month_range",
    "n.token_pos_guess",
    "p.p.token_pos_guess",
    "n.n.token_pos_guess",
    "name",
    NULL};

extern const cst_cart us_nums_cart = {
    us_nums_cart_nodes,
    us_nums_feat_table};
