#pragma once

#include "./indic_num_table.hpp"

// clang-format off

static const char * const indic_kan_digit[11][2] =
{
    { "೦", "ಸೊನ್ನೆ" },
    { "೧", "ಒಂದು" },
    { "೨", "ಎರಡು" },
    { "೩", "ಮೂರು" },
    { "೪", "ನಾಲಕ್ಕು" },
    { "೫", "ಐದು" },
    { "೬", "ಆರು" },
    { "೭", "ಏಳು" },
    { "೮", "ಎಂಟು" },
    { "೯", "ಒಂಬತ್ತು" },
    { nullptr, nullptr },
};

static const char * const indic_kan_two_digit[101][4] =
{
    { "೧", "೦", "ಹತ್ತು", nullptr },
    { "೧", "೧", "ಹನ್ನೊಂದು", nullptr },
    { "೧", "೨", "ಹನ್ನೆರಡು", nullptr },
    { "೧", "೩", "ಹದಿಮೂರು", nullptr },
    { "೧", "೪", "ಹದಿನಾಲ್ಕು", nullptr },
    { "೧", "೫", "ಹದಿನೈದು", nullptr },
    { "೧", "೬", "ಹದಿನಾರು", nullptr },
    { "೧", "೭", "ಹದಿನೇಳು", nullptr },
    { "೧", "೮", "ಹದಿನೆಂಟು", nullptr },
    { "೧", "೯", "ಹತ್ತೊಂಬತ್ತು", nullptr },
    { "೨", "೦", "ಇಪ್ಪತ್ತು", nullptr },
    { "೨", "೧", "ಇಪ್ಪತ್ತೊಂದು", nullptr },
    { "೨", "೨", "ಇಪ್ಪತ್ತೆರಡು", nullptr },
    { "೨", "೩", "ಇಪ್ಪತ್ತಮೂರು", nullptr },
    { "೨", "೪", "ಇಪ್ಪತ್ತನಾಲ್ಕು", nullptr },
    { "೨", "೫", "ಇಪ್ಪತ್ತೈದು", nullptr },
    { "೨", "೬", "ಇಪ್ಪತ್ತಾರು", nullptr },
    { "೨", "೭", "ಇಪ್ಪತ್ತೇಳು", nullptr },
    { "೨", "೮", "ಇಪ್ಪತ್ತೆಂಟು", nullptr },
    { "೨", "೯", "ಇಪ್ಪತ್ತೊಂಬತ್ತು", nullptr },
    { "೩", "೦", "ಮೂವತ್ತು", nullptr },
    { "೩", "೧", "ಮೂವತ್ತೊಂದು", nullptr },
    { "೩", "೨", "ಮೂವತ್ತೆರಡು", nullptr },
    { "೩", "೩", "ಮೂವತ್ತಮೂರು", nullptr },
    { "೩", "೪", "ಮೂವತ್ತನಾಲ್ಕು", nullptr },
    { "೩", "೫", "ಮೂವತ್ತೈದು", nullptr },
    { "೩", "೬", "ಮೂವತ್ತಾರು", nullptr },
    { "೩", "೭", "ಮೂವತ್ತೇಳು", nullptr },
    { "೩", "೮", "ಮೂವತ್ತೆಂಟು", nullptr },
    { "೩", "೯", "ಮೂವತ್ತೊಂಬತ್ತು", nullptr },
    { "೪", "೦", "ನಲವತ್ತು", nullptr },
    { "೪", "೧", "ನಲವತ್ತೊಂದು", nullptr },
    { "೪", "೨", "ನಲವತ್ತೆರಡು", nullptr },
    { "೪", "೩", "ನಲವತ್ತಮೂರು", nullptr },
    { "೪", "೪", "ನಲವತ್ತನಾಲ್ಕು", nullptr },
    { "೪", "೫", "ನಲವತ್ತೈದು", nullptr },
    { "೪", "೬", "ನಲವತ್ತಾರು", nullptr },
    { "೪", "೭", "ನಲವತ್ತೇಳು", nullptr },
    { "೪", "೮", "ನಲವತ್ತೆಂಟು", nullptr },
    { "೪", "೯", "ನಲವತ್ತೊಂಬತ್ತು", nullptr },
    { "೫", "೦", "ಐವತ್ತು", nullptr },
    { "೫", "೧", "ಐವತ್ತೊಂದು", nullptr },
    { "೫", "೨", "ಐವತ್ತೆರಡು", nullptr },
    { "೫", "೩", "ಐವತ್ತಮೂರು", nullptr },
    { "೫", "೪", "ಐವತ್ತನಾಲ್ಕು", nullptr },
    { "೫", "೫", "ಐವತ್ತೈದು", nullptr },
    { "೫", "೬", "ಐವತ್ತಾರು", nullptr },
    { "೫", "೭", "ಐವತ್ತೇಳು", nullptr },
    { "೫", "೮", "ಐವತ್ತೆಂಟು", nullptr },
    { "೫", "೯", "ಐವತ್ತೊಂಬತ್ತು", nullptr },
    { "೬", "೦", "ಅರವತ್ತು", nullptr },
    { "೬", "೧", "ಅರವತ್ತೊಂದು", nullptr },
    { "೬", "೨", "ಅರವತ್ತೆರಡು", nullptr },
    { "೬", "೩", "ಅರವತ್ತಮೂರು", nullptr },
    { "೬", "೪", "ಅರವತ್ತನಾಲ್ಕು", nullptr },
    { "೬", "೫", "ಅರವತ್ತೈದು", nullptr },
    { "೬", "೬", "ಅರವತ್ತಾರು", nullptr },
    { "೬", "೭", "ಅರವತ್ತೇಳು", nullptr },
    { "೬", "೮", "ಅರವತ್ತೆಂಟು", nullptr },
    { "೬", "೯", "ಅರವತ್ತೊಂಬತ್ತು", nullptr },
    { "೭", "೦", "ಎಪ್ಪತ್ತು", nullptr },
    { "೭", "೧", "ಎಪ್ಪತ್ತೊಂದು", nullptr },
    { "೭", "೨", "ಎಪ್ಪತ್ತೆರಡು", nullptr },
    { "೭", "೩", "ಎಪ್ಪತ್ತಮೂರು", nullptr },
    { "೭", "೪", "ಎಪ್ಪತ್ತನಾಲ್ಕು", nullptr },
    { "೭", "೫", "ಎಪ್ಪತ್ತೈದು", nullptr },
    { "೭", "೬", "ಎಪ್ಪತ್ತಾರು", nullptr },
    { "೭", "೭", "ಎಪ್ಪತ್ತೇಳು", nullptr },
    { "೭", "೮", "ಎಪ್ಪತ್ತೆಂಟು", nullptr },
    { "೭", "೯", "ಎಪ್ಪತ್ತೊಂಬತ್ತು", nullptr },
    { "೮", "೦", "ಎಂಬತ್ತು", nullptr },
    { "೮", "೧", "ಎಂಬತ್ತೊಂದು", nullptr },
    { "೮", "೨", "ಎಂಬತ್ತೆರಡು", nullptr },
    { "೮", "೩", "ಎಂಬತ್ತಮೂರು", nullptr },
    { "೮", "೪", "ಎಂಬತ್ತನಾಲ್ಕು", nullptr },
    { "೮", "೫", "ಎಂಬತ್ತೈದು", nullptr },
    { "೮", "೬", "ಎಂಬತ್ತಾರು", nullptr },
    { "೮", "೭", "ಎಂಬತ್ತೇಳು", nullptr },
    { "೮", "೮", "ಎಂಬತ್ತೆಂಟು", nullptr },
    { "೮", "೯", "ಎಂಬತ್ತೊಂಬತ್ತು", nullptr },
    { "೯", "೦", "ತೊಂಬತ್ತು", nullptr },
    { "೯", "೧", "ತೊಂಬತ್ತೊಂದು", nullptr },
    { "೯", "೨", "ತೊಂಬತ್ತೆರಡು", nullptr },
    { "೯", "೩", "ತೊಂಬತ್ತಮೂರು", nullptr },
    { "೯", "೪", "ತೊಂಬತ್ತನಾಲ್ಕು", nullptr },
    { "೯", "೫", "ತೊಂಬತ್ತೈದು", nullptr },
    { "೯", "೬", "ತೊಂಬತ್ತಾರು", nullptr },
    { "೯", "೭", "ತೊಂಬತ್ತೇಳು", nullptr },
    { "೯", "೮", "ತೊಂಬತ್ತೆಂಟು", nullptr },
    { "೯", "೯", "ತೊಂಬತ್ತೊಂಬತ್ತು", nullptr },
    { nullptr, nullptr },
};

const static indic_num_table kan_num_table = {
    "kan",
    &indic_kan_digit,
    &indic_kan_two_digit,
    "ನೂರು",   /* hundred */
    "ಸಾವಿರ", /* thousand */
    "ಲಕ್ಷ",  /* lakh */
    "ಕೋಟಿ", /* crore */
};

// clang-format on
