#pragma once

#include "./indic_num_table.hpp"

// clang-format off

#if 0
static const char * const indic_eng_digit[11][2] =
{
    { "0", "शून्य" },
    { "1", "एक" },
    { "2", "दोन" },
    { "3", "तीन" },
    { "4", "चार" },
    { "5", "पाच" },
    { "6", "सहा" },
    { "7", "सात" },
    { "8", "आठ" },
    { "9", "नऊ" },
    { nullptr, nullptr }
};

static const char * const indic_eng_two_digit[101][4] =
{
    { "1", "0", "दहा",  nullptr },
    { "1", "1", "अकरा",  nullptr },
    { "1", "2", "बारा",  nullptr },
    { "1", "3", "तेरा",  nullptr },
    { "1", "4", "चौदा",  nullptr },
    { "1", "5", "पंधरा",  nullptr },
    { "1", "6", "सोळा",  nullptr },
    { "1", "7", "सतरा",  nullptr },
    { "1", "8", "अठरा",  nullptr },
    { "1", "9", "एकोणीस",  nullptr },
    { "2", "0", "वीस",  nullptr },
    { "2", "1", "एकवीस",  nullptr },
    { "2", "2", "बावीस",  nullptr },
    { "2", "3", "तेवीस",  nullptr },
    { "2", "4", "चोवीस",  nullptr },
    { "2", "5", "पंचवीस",  nullptr },
    { "2", "6", "सव्वीस",  nullptr },
    { "2", "7", "सत्तावीस",  nullptr },
    { "2", "8", "अठ्ठावीस",  nullptr },
    { "2", "9", "एकोणतीस",  nullptr },
    { "3", "0", "तीस",  nullptr },
    { "3", "1", "एकतीस",  nullptr },
    { "3", "2", "बत्तीस",  nullptr },
    { "3", "3", "तेहेतीस",  nullptr },
    { "3", "4", "चौतीस",  nullptr },
    { "3", "5", "पस्तीस",  nullptr },
    { "3", "6", "छत्तीस",  nullptr },
    { "3", "7", "सदतीस",  nullptr },
    { "3", "8", "अडतीस",  nullptr },
    { "3", "9", "एकोणचाळीस",  nullptr },
    { "4", "0", "चाळीस",  nullptr },
    { "4", "1", "एक्केचाळीस",  nullptr },
    { "4", "2", "बेचाळीस",  nullptr },
    { "4", "3", "त्रेचाळीस",  nullptr },
    { "4", "4", "चव्वेचाळीस",  nullptr },
    { "4", "5", "पंचेचाळीस",  nullptr },
    { "4", "6", "सेहेचाळीस",  nullptr },
    { "4", "7", "सत्तेचाळीस",  nullptr },
    { "4", "8", "अठ्ठेचाळीस",  nullptr },
    { "4", "9", "एकोणपन्नास",  nullptr },
    { "5", "0", "पन्नास",  nullptr },
    { "5", "1", "एक्कावन्न",  nullptr },
    { "5", "2", "बावन्न",  nullptr },
    { "5", "3", "त्रेपन्न",  nullptr },
    { "5", "4", "चोपन्न",  nullptr },
    { "5", "5", "पंचावन्न",  nullptr },
    { "5", "6", "छप्पन्न",  nullptr },
    { "5", "7", "सत्तावन्न",  nullptr },
    { "5", "8", "अठ्ठावन्न",  nullptr },
    { "5", "9", "एकोणसाठ",  nullptr },
    { "6", "0", "साठ",  nullptr },
    { "6", "1", "एकसष्ठ",  nullptr },
    { "6", "2", "बासष्ठ",  nullptr },
    { "6", "3", "त्रेसष्ठ",  nullptr },
    { "6", "4", "चौसष्ठ",  nullptr },
    { "6", "5", "पासष्ठ",  nullptr },
    { "6", "6", "सहासष्ठ",  nullptr },
    { "6", "7", "सदुसष्ठ",  nullptr },
    { "6", "8", "अडुसष्ठ",  nullptr },
    { "6", "9", "एकोणसत्तर",  nullptr },
    { "7", "0", "सत्तर",  nullptr },
    { "7", "1", "एक्काहत्तर",  nullptr },
    { "7", "2", "बाहत्तर",  nullptr },
    { "7", "3", "त्र्याहत्तर",  nullptr },
    { "7", "4", "चौर्‍याहत्तर",  nullptr },
    { "7", "5", "पंच्याहत्तर",  nullptr },
    { "7", "6", "शहात्तर",  nullptr },
    { "7", "7", "सत्याहत्तर",  nullptr },
    { "7", "8", "अठ्ठ्याहत्तर",  nullptr },
    { "7", "9", "एकोणऐंशी",  nullptr },
    { "8", "0", "ऐंशी",  nullptr },
    { "8", "1", "एक्क्याऐंशी",  nullptr },
    { "8", "2", "ब्याऐंशी",  nullptr },
    { "8", "3", "त्र्याऐंशी",  nullptr },
    { "8", "4", "चौऱ्याऐंशी",  nullptr },
    { "8", "5", "पंच्याऐंशी",  nullptr },
    { "8", "6", "शहाऐंशी",  nullptr },
    { "8", "7", "सत्त्याऐंशी",  nullptr },
    { "8", "8", "अठ्ठ्याऐंशी",  nullptr },
    { "8", "9", "एकोणनव्वद",  nullptr },
    { "9", "0", "नव्वद",  nullptr },
    { "9", "1", "एक्क्याण्णव",  nullptr },
    { "9", "2", "ब्याण्णव",  nullptr },
    { "9", "3", "त्र्याण्णव",  nullptr },
    { "9", "4", "चौऱ्याण्णव",  nullptr },
    { "9", "5", "पंच्याण्णव",  nullptr },
    { "9", "6", "शहाण्णव",  nullptr },
    { "9", "7", "सत्त्याण्णव",  nullptr },
    { "9", "8", "अठ्ठ्याण्णव",  nullptr },
    { "9", "9", "नव्व्याण्णव",  nullptr },
    { nullptr, nullptr }
};

const static indic_num_table mar_num_table = {
    "mar",
    &indic_eng_digit,
    &indic_eng_two_digit,
    "शंभर",   /* hundred */
    "हजार", /* thousand */
    "लाख",  /* lakh */
    "कोटी", /* crore */
};
#endif

#if 1

static const char * const indic_eng_digit[11][2] =
{
    { "0", "zero" },
    { "1", "one" },
    { "2", "two" },
    { "3", "three" },
    { "4", "four" },
    { "5", "five" },
    { "6", "six" },
    { "7", "seven" },
    { "8", "eight" },
    { "9", "nine" },
    { nullptr, nullptr }
};

static const char * const indic_eng_two_digit[101][4] =
{
    { "0", "0", nullptr, nullptr },
    { "0", "1", "and", "one" },
    { "0", "2", "and", "two" },
    { "0", "3", "and", "three" },
    { "0", "4", "and", "four" },
    { "0", "5", "and", "five" },
    { "0", "6", "and", "six" },
    { "0", "7", "and", "seven" },
    { "0", "8", "and", "eight" },
    { "0", "9", "and", "nine" },
    { "1", "0", "ten", nullptr },
    { "1", "1", "eleven", nullptr },
    { "1", "2", "twelve", nullptr },
    { "1", "3", "thirteen", nullptr },
    { "1", "4", "fourteen", nullptr },
    { "1", "5", "fifteen", nullptr },
    { "1", "6", "sixteen", nullptr },
    { "1", "7", "seventeen", nullptr },
    { "1", "8", "eighteen", nullptr },
    { "1", "9", "nineteen", nullptr },
    { "2", "0", "twenty", nullptr },
    { "2", "1", "twenty", "one" },
    { "2", "2", "twenty", "two" },
    { "2", "3", "twenty", "three" },
    { "2", "4", "twenty", "four" },
    { "2", "5", "twenty", "five" },
    { "2", "6", "twenty", "six" },
    { "2", "7", "twenty", "seven" },
    { "2", "8", "twenty", "eight" },
    { "2", "9", "twenty", "nine" },
    { "3", "0", "thirty", nullptr },
    { "3", "1", "thirty", "one" },
    { "3", "2", "thirty", "two" },
    { "3", "3", "thirty", "three" },
    { "3", "4", "thirty", "four" },
    { "3", "5", "thirty", "five" },
    { "3", "6", "thirty", "six" },
    { "3", "7", "thirty", "seven" },
    { "3", "8", "thirty", "eight" },
    { "3", "9", "thirty", "nine" },
    { "4", "0", "forty", nullptr },
    { "4", "1", "forty", "one" },
    { "4", "2", "forty", "two" },
    { "4", "3", "forty", "three" },
    { "4", "4", "forty", "four" },
    { "4", "5", "forty", "five" },
    { "4", "6", "forty", "six" },
    { "4", "7", "forty", "seven" },
    { "4", "8", "forty", "eight" },
    { "4", "9", "forty", "nine" },
    { "5", "0", "fifty", nullptr },
    { "5", "1", "fifty", "one" },
    { "5", "2", "fifty", "two" },
    { "5", "3", "fifty", "three" },
    { "5", "4", "fifty", "four" },
    { "5", "5", "fifty", "five" },
    { "5", "6", "fifty", "six" },
    { "5", "7", "fifty", "seven" },
    { "5", "8", "fifty", "eight" },
    { "5", "9", "fifty", "nine" },
    { "6", "0", "sixty", nullptr },
    { "6", "1", "sixty", "one" },
    { "6", "2", "sixty", "two" },
    { "6", "3", "sixty", "three" },
    { "6", "4", "sixty", "four" },
    { "6", "5", "sixty", "five" },
    { "6", "6", "sixty", "six" },
    { "6", "7", "sixty", "seven" },
    { "6", "8", "sixty", "eight" },
    { "6", "9", "sixty", "nine" },
    { "7", "0", "twenty", nullptr },
    { "7", "1", "seventy", "one" },
    { "7", "2", "seventy", "two" },
    { "7", "3", "seventy", "three" },
    { "7", "4", "seventy", "four" },
    { "7", "5", "seventy", "five" },
    { "7", "6", "seventy", "six" },
    { "7", "7", "seventy", "seven" },
    { "7", "8", "seventy", "eight" },
    { "7", "9", "seventy", "nine" },
    { "8", "0", "eighty", nullptr },
    { "8", "1", "eighty", "one" },
    { "8", "2", "eighty", "two" },
    { "8", "3", "eighty", "three" },
    { "8", "4", "eighty", "four" },
    { "8", "5", "eighty", "five" },
    { "8", "6", "eighty", "six" },
    { "8", "7", "eighty", "seven" },
    { "8", "8", "eighty", "eight" },
    { "8", "9", "eighty", "nine" },
    { "9", "0", "ninety", nullptr },
    { "9", "1", "ninety", "one" },
    { "9", "2", "ninety", "two" },
    { "9", "3", "ninety", "three" },
    { "9", "4", "ninety", "four" },
    { "9", "5", "ninety", "five" },
    { "9", "6", "ninety", "six" },
    { "9", "7", "ninety", "seven" },
    { "9", "8", "ninety", "eight" },
    { "9", "9", "ninety", "nine" },
    { nullptr, nullptr }
};


const static indic_num_table eng_num_table = {
    "eng",
    &indic_eng_digit,
    &indic_eng_two_digit,
    "hundred",
    "thousand",
    "lakh",
    "crore"
};

#endif

// clang-format on
