#include "Buffer.h"
void Buffer::atualizarCaravanas(const vector<Caravana*>& caravanas) {
    for (const Caravana* caravana : caravanas) {
        int lin = caravana->obterLinha();
        int col = caravana->obterColuna();
        buffer[lin * colunas + col] = '1'; // Represent the caravan
    }
}


// Construtor para iniciar o tamanho do buffer
Buffer::Buffer(int l, int c) : linhas(l), colunas(c) {
    buffer = make_unique<char[]>(linhas * colunas);
    limpar();  // limpa tudo
}

// Clear the buffer (reset to empty state)
void Buffer::limpar() {
    fill(buffer.get(), buffer.get() + linhas * colunas, ' ');  // Fill with spaces (empty cells)
}

// Update the map information in the buffer
void Buffer::atualizarBuffer (const Mapa& mapa) {
    for (int r = 0; r < linhas; ++r) {
        for (int c = 0; c < colunas; ++c) {
            buffer[r * colunas + c] = mapa.obterCelula(r, c);  // Copy map information to buffer
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