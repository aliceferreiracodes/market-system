# mercado.c

mercado.c is a program written in C that simulates a simple market system.


## 🛠️ Features

The main features of the market system are:

- List of registered items
- Wishlist
- Shopping cart

In all of them, you can perform operations such as adding, searching, and removing products, as well as displaying the entire list.


## 👩‍💻 Development

The market system was developed with the functionalities mentioned above, and for that, the following functions were created:

`cadastrar_produto()` - Registers a product in the market's item list

`listar_produtos()` - Displays product information within a specific range of the list

`pegar_produto_por_codigo()` - Searches for a product in the registered list

`remover_produto()` - Removes a product by its code

`add_lista_de_desejos()` - Adds an item to the wishlist

`buscar_ld()` - Searches for a product in the wishlist

`remover_ld()` - Removes a product from the wishlist

`comprar_produto()` - Adds a product to the shopping cart

`visualizar_carrinho()` - Displays the items in the shopping cart

`remover_carrinho()` - Removes an item from the shopping cart

`tem_no_carrinho()` - Searches for an item in the shopping cart

`fechar_pedido()` - Displays the total purchase amount and completes the order, clearing the cart

## ⌨️ How to Use

Here are some instructions on how to use the system:

### Compilation and Execution

To compile and run the `mercado.c` file, you need to have GCC installed and set as an environment variable on your computer.

Once that is done, open a terminal in the folder where the `mercado.c` file is located and enter the following commands:

```
$ gcc mercado.c -o mercado
$ ./mercado
```
These commands will compile and run the program, respectively.

### Usage

When you run the program, the following text will appear in your terminal:

```
  - HYRULE MARKET -  

-> Welcome to the Hyrule Market shopping system! Here you have three main features:  
the list of registered products, the wishlist, and the shopping cart. See the actions you can perform in the system:  

- Registered Product List  
1 - Register a product  
2 - View the list of registered products  
3 - Search for a product by code and display its information  
4 - Remove a product from the registered product list  

- Wishlist  
5 - Add a product to your wishlist  
6 - View your wishlist  
7 - Search for a product by code in your wishlist and display its information  
8 - Remove a product from the wishlist  

- Shopping Cart  
9 - Add a product to the cart  
10 - View the cart  
11 - Search for a product by code in the cart and display its information  
12 - Remove a product from the cart  
13 - Complete the order and finalize your purchase  

14 - Exit the system  

-> Enter the number of the action you want to perform:
```

To use the program, simply type the number corresponding to the action you want to perform in the market system and press Enter.
After entering your option, instructions related to the chosen action will appear.

This prompt will appean on the screen every time an action is finished, except if you type the option 14, which will close the program.
