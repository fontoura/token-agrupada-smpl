/*
MIT License

Copyright (c) 2021 Felipe Michels Fontoura

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define AGRUPAR_TOKEN2(x, y)        _create_token2(x, y)
#define SEPARAR_TOKEN2(tkn, x, y)   _extract_token2(&(tkn), &(x), &(y))
#define AGRUPAR_TOKEN3(x, y, z)     _create_token3(x, y, z)
#define SEPARAR_TOKEN3(tkn, x, y,z) _extract_token3(&(tkn), &(x), &(y), &(z))

int _create_token2(int x, int y);
void _extract_token2(int* tkn, int* x, int* y);
int _create_token3(int x, int y, int z);
void _extract_token3(int* tkn, int* x, int* y, int* z);