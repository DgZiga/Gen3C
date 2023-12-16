
Passaggi:
A 0x806F282 (control loop of normal menu) c'è un hijack, che manda al codice C input_handler.
input_handler controlla se sia stato premuto A, Select, start o B e conosce se al momneto siamo nel menu principale o nel side.
DA lì input_handler eventualmente passa il controllo a poketools per l'apertura delle scelte.
Se viene scelta un'opzione del menù temporaneo, il controllo passa all'engine che legge la config del menu e reagisce appropriatamente

TODOS:
Nome menu che si riflette sul menu configurabile
Callabile da oggetto FATTO (La macro BY_ITEM prende un id dell'array di feature implementate e crea 3 funzioni La funzione gui_##id##_new_gui_by_item se messa come offset di un item apre quella gui)
inserimento al posto dell'oggetto automatico?
Bg deve essere una func provider per customizzarla FATTO
grafichetta swap? whynot

in this demo, the teachy tv redirects to gui_1 (main.s)