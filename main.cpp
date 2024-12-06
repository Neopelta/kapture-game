#include <iostream>

#include "include/units/chairACanon.h"
#include "include/units/eclaireur.h"
#include "include/units/troupeDeChoc.h"

int main() {
    eclaireur e1 = eclaireur();
    eclaireur e2 = eclaireur();
    chairACanon c1 = chairACanon();
    chairACanon c2 = chairACanon();
    troupeDeChoc tc1 = troupeDeChoc();
    troupeDeChoc tc2 = troupeDeChoc();

    e1.fight(e2);
    e1.fight(tc2);
    e1.fight(c2);

    std::cout << std::endl;

    c1.fight(e2);
    c1.fight(tc2);
    c1.fight(c2);

    std::cout << std::endl;

    tc1.fight(e2);
    tc1.fight(tc2);
    tc2.fight(c2);

    return 0;
}
