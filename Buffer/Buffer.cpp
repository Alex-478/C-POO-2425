#include "Buffer.h"

Buffer::Buffer() : linhas(0), colunas(0), buffer(nullptr) {}

// Construtor para iniciar o tamanho do buffer
Buffer::Buffer(int l, int c) : linhas(l), colunas(c) {
    buffer = make_unique<char[]>(linhas * colunas);
    limpar();  // limpa tudo
}

//Construtor Copia
Buffer::Buffer(const Buffer& other) : linhas(other.linhas), colunas(other.colunas) {
    buffer = make_unique<char[]>(linhas * colunas);
    copy(other.buffer.get(), other.buffer.get() + linhas * colunas, buffer.get());
}

Buffer& Buffer::operator=(const Buffer& other) {
    if (this == &other) return *this; // self-assignment check

    linhas = other.linhas;
    colunas = other.colunas;
    // Aloca novo espaço para o buffer e copia os dados
    buffer = std::make_unique<char[]>(linhas * colunas);
    std::copy(other.buffer.get(), other.buffer.get() + (linhas * colunas), buffer.get());

    return *this;
}


char* Buffer::obterDados() {
    return buffer.get();
}
// Copia o estado do buffer para outro array
void Buffer::copiarEstado(char* destino) const {
    copy(buffer.get(), buffer.get() + (linhas * colunas), destino);
}
int Buffer::obterLinhas() const { return linhas; }
int Buffer::obterColunas() const { return colunas; }


// Clear the buffer (reset to empty state)
void Buffer::limpar() {
    fill(buffer.get(), buffer.get() + linhas * colunas, ' ');  // Fill with spaces (empty cells)
}

// Update the map information in the buffer
void Buffer::atualizarBuffer (const Mapa& mapa) {
    for (int r = 0; r < mapa.obterLinhas(); ++r) {
        for (int c = 0; c < mapa.obterColunas(); ++c) {
            buffer[r * mapa.obterColunas() + c] = mapa.obterCelula(r, c);  // Copy map information to buffer
        }
    }


}


// Print the buffer to the screen
void Buffer::mostrar() const {
    for (int r = 0; r < linhas; ++r) {
        for (int c = 0; c < colunas; ++c) {
            cout << buffer[r * colunas + c] << " ";  // Print each cell with a space
        }
        cout << endl;  // New line after each row
    }
}

