#pragma once

#include "flite/hrg/item.hpp"
#include "flite/hrg/relation.hpp"

#include "flite/utils/features.hpp"
#include "flite/utils/file.hpp"
#include "flite/utils/val.hpp"

#define CST_CART_OP_NONE 255
#define CST_CART_OP_LEAF 255
#define CST_CART_OP_IS 0
#define CST_CART_OP_IN 1
#define CST_CART_OP_LESS 2
#define CST_CART_OP_GREATER 3
#define CST_CART_OP_MATCHES 4
#define CST_CART_OP_EQUALS 5

typedef struct cst_cart_node_struct {
    unsigned char feat;
    unsigned char op;
    /* yes is always the next node */
    unsigned short no_node; /* or answer index */
    const cst_val* val;
} cst_cart_node;

typedef struct cst_cart_struct {
    const cst_cart_node* rule_table;
    const char* const* feat_table;
} cst_cart;

void delete_cart(cst_cart* c);

CST_VAL_USER_TYPE_DCLS(cart, cst_cart)

const cst_val* cart_interpret(cst_item* item, const cst_cart* tree);
