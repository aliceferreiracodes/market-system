#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct // Product struct
{
    int codigo; 
    char nome[30]; 
    double preco; 

} Produto;

typedef struct // Shopping cart struct
{ 
    Produto produto; 
    int quantidade; 
    
} Carrinho;

// Global variables
int itens_cadastrados = 0; // itens_cadastrados: stores the current number of items in the registered product list
int itens_ld = 0; // itens_ld: stores the current number of items in the wishlist
int itens_carrinho = 0; // itens_carrinho: stores the current number of items in the shopping cart


// Description of the functions
int menu(); // Displays the menu

Produto cadastrar_produto(int tam_lista); // Registers the product in the market's product list

void listar_produtos(Produto *lista, int inicio, int fim); // Displays information about products in a given range

void pegar_produto_por_codigo(Produto *lista, int tam_lista); // Searches for products in the registered product list

void remover_produto(Produto *lista, int tam_lista); // Removes product by its code

void add_lista_de_desejos(Produto *cadastrados, Produto *lista_desejos, int n_cadastrados, int n_lista_desejos); // Adds product to the wishlist
 
void buscar_ld(Produto *lista, int tam_lista); // Searches for product in the wishlist

void remover_ld(Produto *lista, int tam_lista); // Removes product from the wishlist

void comprar_produto(Produto *cadastrados, Carrinho *lista_carrinho, int n_cadastrados, int n_carrinho); // Adds product to the shopping cart

void visualizar_carrinho(Carrinho *lista, int inicio, int fim); // Displays shopping cart

void remover_carrinho(Carrinho *lista, int tam_carrinho); // Removes an item from the shopping cart

void tem_no_carrinho(Carrinho *lista, int tam_carrinho); // Searches for item in the shopping cart

void fechar_pedido(Carrinho *lista, int tam_carrinho); // Finishes order and calculates final price


// Main function
int main()
{
    // Creating product list, shopping cart and wishlist
    Produto produtos[50];
    Carrinho carrinho[50];
    Produto lista_de_desejos[50];
    int opcao;  // Variable that stores user's option
    

    while(1)
    {
        if (opcao == 14)
            break;

        opcao = menu();

        switch (opcao)
        {
            case 1:
            // Register product
                produtos[itens_cadastrados] = cadastrar_produto(itens_cadastrados);
                break;

            case 2:
            // List registered products
                printf("\n-> Registered products:\n");
                listar_produtos(produtos, 0, itens_cadastrados);
                break;

            case 3:
            // Search for products in the registered product list
                pegar_produto_por_codigo(produtos, itens_cadastrados);
                break;

            case 4:
            // Remove product in the registered product list
                remover_produto(produtos, itens_cadastrados);
                break;

            case 5:
            // Add to wishlist
                add_lista_de_desejos(produtos, lista_de_desejos, itens_cadastrados, itens_ld);
                break;

            case 6:
            // Display wishlist
                printf("\n-> Wishlist:\n");
                listar_produtos(lista_de_desejos, 0, itens_ld);
                break;

            case 7:
            // Search wishlist
                buscar_ld(lista_de_desejos, itens_ld);
                break;

            case 8:
            // Remove from wishlist
                remover_ld(lista_de_desejos, itens_ld);
                break;

            case 9:
            // Add to shopping cart
                comprar_produto(produtos, carrinho, itens_cadastrados, itens_carrinho);
                break;

            case 10:
            // Display shopping cart
                printf("\n-> Shopping cart:\n");
                visualizar_carrinho(carrinho, 0, itens_carrinho);
                break;

            case 11:
            // Search shopping cart
                tem_no_carrinho(carrinho, itens_carrinho);
                break;

            case 12:
            // Remove from shopping cart
                remover_carrinho(carrinho, itens_carrinho);
                break;

            case 13:
            // Finish order
                fechar_pedido(carrinho, itens_carrinho);
                break;

            case 14:
                printf("\n->It was a pleasure to help! Come back soon!\n\n");
                break;

            default:
                break;
        }
    }

    return 0;
}


int menu()
{
    int opcao; 

    // System presentation and instructions
    printf("\n\n  - HYRULE MARKET -  \n");

    printf("\n-> Welcome to Hyrule Market's shopping system! Here, you have 3 main features: \n");
    printf("the registered products list, the wishlist and the shopping cart. These are the actions you can perform in the system:\n");
    
    printf("\n- Registered Product List\n");
    printf("1 - Register a product\n");
    printf("2 - View the list of registered products\n");
    printf("3 - Search for a product by code and display its information\n");
    printf("4 - Remove a product from the registered product list\n");

    printf("\n- Wishlist\n");
    printf("5 - Add a product to your wishlist\n");
    printf("6 - View your wishlist\n");
    printf("7 - Search for a product by code in your wishlist and display its information\n");
    printf("8 - Remove a product from the wishlist\n");

    printf("\n- Shopping Cart\n");
    printf("9 - Add a product to the cart\n");
    printf("10 - View the cart\n");
    printf("11 - Search for a product by code in the cart and display its information\n");
    printf("12 - Remove a product from the cart\n");
    printf("13 - Complete the order and finalize your purchase\n");

    printf("\n14 - Exit the system\n");

    // Option input
    printf("\n-> Enter the number of the action you want to perform: ");
    scanf("%i", &opcao);
    getchar();

    while (opcao > 14 || opcao < 1) // Invalid input treatment
    {
        printf("-> This option is invalid. Please, insert a valid option: ");
        scanf("%i", &opcao);
        getchar();
    }

    return opcao;
}


Produto cadastrar_produto(int tam_lista)
{
    Produto novo_produto;

    // Name validation
    bool nome_valido = false;

    while (nome_valido == false)
    {
        printf("-> Insert the name of the product you want to register: "); // Insert name
        if (fgets(novo_produto.nome, 30, stdin))
        {
            novo_produto.nome[strcspn(novo_produto.nome, "\n")] = 0; // Remove new line
            nome_valido = true; 

            for (int i = 0; i < strlen(novo_produto.nome); i++) // Iterate through name
            { 
                // Invalid name treatment
                if (isalpha(novo_produto.nome[i]) == 0 && novo_produto.nome[i] != ' ') 
                {
                    printf("-> This name is invalid. Type a name that contains letters only.\n"); 
                    nome_valido = false; 
                    break;
                }           
            }
        }
        else
        {
            printf("-> Name input error.\n");
            exit(1);
        }  
    }

    char input_preco[20];
    char *ptr;
    bool preco_valido = false;

    while (preco_valido == false)
    {
        printf("-> Insert the price of the product: "); // Insert price
        if(fgets(input_preco, 20, stdin))
        {
            input_preco[strcspn(input_preco, "\n")] = 0; // Remove new line
            preco_valido = true;

            novo_produto.preco = strtod(input_preco, &ptr); // Convert int to double

            if (*ptr != '\0') // Price validadion
            {
                printf("-> This price is invalid. Insert a number.\n");
                preco_valido = false;
            }
                
        }
        else
        {
            printf("Price input error.\n");
            exit(1);
        }
    }

    novo_produto.codigo = tam_lista + 1; // Assign product's code
    itens_cadastrados++;

    return novo_produto;
}


void listar_produtos(Produto *lista, int inicio, int fim)
{
    for (int i = inicio; i < fim; i++)
    {
        printf("\nCode: %i\n", lista[i].codigo);
        printf("Name: %s\n", lista[i].nome);
        printf("Price: $%.2f\n", lista[i].preco);
    }
}


void pegar_produto_por_codigo(Produto *lista, int tam_lista)
{
    int codigo;
    printf("\n-> Insert the code of the product you want to search in the registered product list: "); // Code input
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    if (codigo < 1 || codigo > tam_lista)
        printf("-> Sorry! We couldn't find any product with this code in our registered product list.\n");
    else 
    {
        // If so, list product
        printf("-> The product was found:\n");
        listar_produtos(lista, codigo - 1, codigo); 
    }
}


void remover_produto(Produto *lista, int tam_lista)
{
    // Code input
    int codigo;
    printf("\n-> Insert the code of the product you want to remove from the registered product list: "); 
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    if (codigo < 1 || codigo > tam_lista)
        printf("-> Sorry! We couldn't find any product with this code in our registered product list.\n");
    else 
    {
        // If so, start remotion loop
        for (int i = codigo - 1; i < tam_lista; i++)
        {
            lista[i] = lista[i + 1];
            lista[i].codigo = i + 1;
        }

        itens_cadastrados--;

        printf("-> Product removed successfully!\n");
    }
}


void add_lista_de_desejos(Produto *cadastrados, Produto *lista_desejos, int n_cadastrados, int n_lista_desejos)
{
    // Code input
    int codigo;
    printf("\n-> Insert the code of the product you want to add to your wishlist: "); 
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    if (codigo < 1 || codigo > n_cadastrados)
        printf("-> Sorry! We couldn't find any product with this code in our registered product list.\n");
    else 
    {
        for (int i = 0; i < n_lista_desejos; i++) // Verify if product has already been added
        {
            if (codigo == lista_desejos[i].codigo)
            {
                printf("\n-> This product has already been added to your wishlist.\n");
                return;
            }
        }

        lista_desejos[n_lista_desejos] = cadastrados[codigo - 1];
        itens_ld++;
        printf("Product added successfully!\n");
    }
}


void buscar_ld(Produto *lista, int tam_lista)
{
    bool achou_produto = false;
    int codigo;
    printf("\n-> Insert the code of the product you want to search in your wishlist: "); // Code input
    scanf("%i", &codigo);
    getchar();

    for (int i = 0; i < tam_lista; i++)
    {
        if (codigo == lista[i].codigo) // Display product
        {
            printf("\n-> The product was found:\n");
            achou_produto = true;
            listar_produtos(lista, i, i + 1);

            break;
        }
    }

    // Print error message if code is not found
    if (achou_produto == false)
        printf("-> Sorry! We couldn't find any product with this code in your wishlist.\n");
}


void remover_ld(Produto *lista, int tam_lista)
{
    bool achou_produto = false;
    int indice_produto;

    // Code input
    int codigo;
    printf("\n-> Insert the code of the product you want to remove from your wishlist: "); 
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    for (int i = 0; i < tam_lista; i++)
    {
        if (codigo == lista[i].codigo) // Remove product
        {
            achou_produto = true;
            indice_produto = i;

            for (int j = indice_produto; j < tam_lista; j++)
            {
                lista[j] = lista[j + 1];
            }

            itens_ld--;
            
            printf("-> Product removed successfully!\n");
            break;
        }
    }

    // Print error message if code is not found
    if (achou_produto == false)
        printf("-> Sorry! We couldn't find any product with this code in your wishlist.\n");
}


void comprar_produto(Produto *cadastrados, Carrinho *lista_carrinho, int n_cadastrados, int n_carrinho)
{
    Carrinho novo_item;
    bool produto_repetido = false;

    // Code input
    int codigo;
    printf("\n-> Insert the code of the product you want to add to your cart: "); 
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    if (codigo < 1 || codigo > n_cadastrados)
        printf("-> Sorry! We couldn't find any product with this code in our registered product list.\n");
    else 
    {
        // Increase quantity if product is repeated
        for (int i = 0; i < n_carrinho; i++)
        {
            if (lista_carrinho[i].produto.codigo == codigo)
            {
                produto_repetido = true;
                lista_carrinho[i].quantidade++;
            }
        }

        if (produto_repetido == false) // In case it's not repeated, add it for the first time
        {
            lista_carrinho[n_carrinho].produto = cadastrados[codigo - 1];
            lista_carrinho[n_carrinho].quantidade = 1;
            itens_carrinho++;
        }
        
        printf("Product added successfully!\n");
    }
}


void visualizar_carrinho(Carrinho *lista, int inicio, int fim)
{
    for (int i = inicio; i < fim; i++)
    {
        printf("\nProduct: %s\n", lista[i].produto.nome);
        printf("Quantity: %i\n", lista[i].quantidade);
        printf("Code: %i\n", lista[i].produto.codigo);
        printf("Price: $%.2f\n", lista[i].produto.preco);
    }
}


void remover_carrinho(Carrinho *lista, int tam_carrinho)
{
    bool achou_produto = false;
    bool produto_repetido = false;
    int indice_produto;

    // Code input
    int codigo;
    printf("\n-> Insert the code of the product you want to remove from your cart: "); 
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    for (int i = 0; i < tam_carrinho; i++)
    {
        if (codigo == lista[i].produto.codigo)
        {
            indice_produto = i;
            achou_produto = true;

            // Decrease quantity if product is repeated
            if (lista[i].quantidade > 1)
            {
                produto_repetido = true;
                lista[i].quantidade--;
            }
            else // Remove product if it's not repeated
            {
                for (int j = indice_produto; j < tam_carrinho; j++)
                {
                    lista[j] = lista[j + 1];
                }

                itens_carrinho--;
            }
            
            printf("-> Product removed successfully!\n");
            break;
        }
    }

    // Print error message if product is not found
    if (achou_produto == false)
        printf("-> Sorry! We couldn't find any product with this code.\n");
}


void tem_no_carrinho(Carrinho *lista, int tam_carrinho)
{
    bool achou_produto = false; 

    int codigo;
    printf("\n-> Insert the code of the product you want to search in your cart: "); // Code input
    scanf("%i", &codigo);
    getchar();

    // Verify if code is in the list
    for (int i = 0; i < tam_carrinho; i++)
    {
        if (codigo == lista[i].produto.codigo) // Display product
        {
            printf("\n-> The product was found: \n");
            achou_produto = true;
            visualizar_carrinho(lista, i, i + 1);

            break;
        }
    }

    // Print error message if product is not found
    if (achou_produto == false)
        printf("-> Sorry! We couldn't find any product with this code in your cart.\n");
}


void fechar_pedido(Carrinho *lista, int tam_carrinho)
{
    float valor_total;
    char opt;
    
    printf("\n-> These are the products included in your order:\n"); // Display shopping cart
    visualizar_carrinho(lista, 0, tam_carrinho);

    for (int i = 0; i < tam_carrinho; i++) // Calculate total price
        valor_total += lista[i].produto.preco * lista[i].quantidade;

    printf("\n-> Total price: $%.2f\n", valor_total); // Print total price

    printf("\n-> Finish order? (\"y\" for yes e \"n\" for no): "); // Confirm order
    scanf("%c", &opt);
    tolower(opt);

    // Check answer
    if (opt == 'y')
    {
        itens_carrinho = 0;
        printf("\n-> Thank you for your order! Come back soon!\n");
    }
    else if (opt == 'n')
    {
        printf("\n-> Alright!\n");
    }
    else    
        printf("\n-> Invalid option.\n");
}
