Pentru a citi din d.in am folosit functiile fgets impreuna cu strtok pentru a separa numarul de playeri de numele echipei.

Numele echipei l-am concatenat folosind strcat. Numele, prenumele si punctajul jucatorilor au fost citite in mod asemanator.

In continuare am format nodul de lista care contine numarul de jucatori din echipa, numele echipei, si informatiile jucatorilor. Am folosit functia add_to_beginning pentru a introduce nodul in lista. De asemenea am stocat scorurile echipei (suma punctajelor jucatorilor / numarul de playeri) intr-un vector care este folosit pentru task 2.

Pentru task-ul 1 am iterat prin capul listei cu un nod suplimentar "current" afisand in r.out numele echipei.

pentru task-ul 2 am aflat multiplul lui 2 mai mic sau egal cu numarul de echipe ("x" in cod) pentru a determina cate echipe trebuie sa eliminam (numarul de echipe - x), am sortat vectorul cu scorurile echipei folosind bubble sort si am eliminat primele (numarul de echipe - x) echipe.

Pentru task-ul 3 am adaugat echipele intr-o coada din lista folosind enqueue, dupa care am dat pop la echipe 2 cate doua si am comparat infomratiile, adaugand in stiva de invingatori echipa cu punctaj mai mare si in stiva de pierzatori echipele cu punctaj mai mic folosind push (echipa castigatoare primind un punct), la final folosind freeStack pentru a elibera stiva de pierzatori. Functia este apelata recursiv pana cand coada este goala.

In plus, cand stiva de castigatori are 8 echipe, le adaugam intr-o lista folosind add_at_beginning, pe care o folosim la task-ul 4.

La task-ul 4 am folosit lista salvata la task-ul anterior pentru a introduce echipele intr-un BST care va fi afisat prin parcurgerea in inordine. BST-ul a fost format prin comparatia atat a punctajului cat si a numelui (pentru a fii ordonat descrescator).

Task-ul 5 nu este implementat in totalitate, doar agaugarea in AVL a listei salvate la punctul 3.

Consider ca aceasta metoda de implementare este costisitoare din punct de vedere al memoriei, insa este rapida.