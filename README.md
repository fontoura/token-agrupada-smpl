# Atributos compostos no `smpl`
## Motivação

Esta pequena biblioteca foi feita para auxiliar a programação de simulações envolvendo a biblioteca "smpl". A biblioteca "smpl" de simulação de eventos discretos foi criada por Myron H. MacDougall.

Com a biblioteca SMPL, os eventos são agendados usando a função `schedule`.


```C
schedule(ev, time, tkn);
```

Durante a simulação, os eventos são recebidos usando a função `cause`.

```C
int ev, tkn;
// ...
cause(&ev, &tkn);
```

Em ambos os casos, `ev` é um `int` que identifica o tipo do evento e `tkn` é o parâmetro adicional, também do tipo `int`, e que representa algum atributo adicional do evento. Normalmente o atributo `tkn` é usado para identificar o elemento da simulação sobre o qual o evento ocorre.

Porém, há casos em que um evento precisa receber mais de um atributo, ou o atributo é um valor que não cabe em um `int`. Neste caso, o procedimento padrão ao usar a biblioteca "smpl" seria criar uma `struct` que representa os atributos do evento, e enviar seu ponteiro no `schedule`. Depois, os atributos deveriam ser lidos no `cause` (sempre lembrando de gerenciar a memória).

```C
// definição da struct
typedef struct {
    int a1;
    int a2;
} atributo_composto;

// ...

// disparo do evento
atributo_composto* ac = (atributo_composto*) malloc(sizeof(atributo_composto));
ac->a1 = 1; // ou qualquer outro valor
ac->a2 = 2; // ou qualquer outro valor
schedule(EVENTO_COMPOSTO, 0.0, (int) (void*) ac);

// captura do evento
int ev, tkn;
cause(&ev, &tkn);
switch (ev) {
    // ...

    case EVENTO_COMPOSTO:
        atributo_composto* ac = (atributo_composto*) tkn;
        int a1 = ac->a1;
        int a2 = ac->a2;
        free((void*) tkn);
        ac = NULL;

        // agora pode usar o a1 e o a2.

        // ...
        break;

    // ...
```

Este paradigma funciona se o executável for compilado em 32 bit (o `int` e o `void*` tem o mesmo tamanho). Portanto, isto funcionava perfeitamente quando o `smpl` foi criado. Porém, atualmente a maioria dos computadores usam arquitetura de 64 bits. Em 64 bits, o código acima não funciona (pois quando é feito cast de `void*` para `int` no `schedule` é possível que informação seja perdida, e o cast inverso feito no `cause` não vai funcionar como esperado).

Considero ainda que o paradigma, apesar de funcionar, prejudica severamente a legibilidade do código. O código ganha uma complexidade desnecessária para permitir o envio de atributos compostos para o `smpl`.

## Uso

Para usar a biblioteca, adicione-a ao seu makefile, tanto para build quanto para link.

O uso é simples, e envolve macros especiais: `AGRUPAR_TOKEN` e `SEPARAR_TOKEN`. Para mandar dois atributos para um evento, faz-se assim:

```C
cause(ev, time, AGRUPAR_TOKEN2(a1, a2));
```

Para tratar o evento, faz-se o seguinte:

```C
int ev, tkn;
schedule(&ev, &tkn);
// ...
int a1, a2;
SEPARAR_TOKEN2(tkn, a1, a2);
// agora pode usar o a1 e o a2.
```

A biblioteca também suporta o caso de três atributos. Para mandar três atributos para um evento, faz-se assim:

```C
schedule(ev, time, AGRUPAR_TOKEN2(a1, a2, a3));
```

Para tratar o evento, faz-se o seguinte:

```C
int ev, tkn;
cause(&ev, &tkn);
// ...
int a1, a2, a3;
SEPARAR_TOKEN2(tkn, a1, a2, a3);
// agora pode usar o a1, a2 e a3.
```

## Licença
Esta biblioteca está liberada sob licença MIT, conforme arquivo LICENSE em anexo.