Configuració de la Base de Dades

Per tal que l'aplicació funcioni correctament en qualsevol entorn, la connexió a la base de dades no està codificada dins del programa, sinó que es llegeix d'un fitxer de configuració extern.

Instruccions de configuració:

1.  A l'arrel del projecte (al mateix nivell que l'executable), ha d'existir un fitxer anomenat **`configuracio.env`**.
2.  Aquest fitxer ha de contenir els paràmetres de connexió a la teva base de dades MySQL local en el format d'arguments estàndard d'ODB.

Exemple de contingut per al fitxer `configuracio.env`:

DB_USER=...
DB_PASS=...
DB_NAME=...
DB_HOST=...
