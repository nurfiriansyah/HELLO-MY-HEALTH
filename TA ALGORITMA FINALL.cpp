#include <iostream>
#include <cstdlib>
using namespace std;

void judul() {
    cout << "=== SISTEM SIMULASI MANAJEMEN ENERGI BUATAN ===\n";
}

double totalEnergi(double angin, double air, double surya) {
    return angin + air + surya;
}

double prediksiKebutuhan(double nilaiSaatIni, int mode) {
    double faktor = 0.10;

    if (mode == 1)
        return nilaiSaatIni * (1 + faktor);
    else
        return nilaiSaatIni * (1 + faktor * 4);
}

string kategoriTarif(double tarif, double pendapatan) {
    if (tarif <= pendapatan * 0.05) return "Terjangkau";
    else if (tarif <= pendapatan * 0.10) return "Menengah";
    else return "Mahal";
}

double angin = 0, air = 0, surya = 0;
double total = 0;

string sektor[100];
double kebutuhan[100];
int jumlahSektor = 0;

double biayaProduksi = 0;
double biayaDistribusi = 0;
double pendapatanSektor[100];
double tarifPerKwh[100];
string kategoriHarga[100];

void case1() {
    cout << "\nMasukkan energi angin  : "; cin >> angin;
    cout << "Masukkan energi air    : "; cin >> air;
    cout << "Masukkan energi surya  : "; cin >> surya;

    total = totalEnergi(angin, air, surya);
    cout << "Total energi = " << total << " kWh\n";
}

void case2() {

    cout << "\nMasukkan jumlah sektor: ";
    cin >> jumlahSektor;

    if (jumlahSektor > 100) {
        cout << "Kebanyakan sektor!\n";
        jumlahSektor = 100;
    }

    for (int i = 0; i < jumlahSektor; i++) {
        cout << "Nama sektor ke-" << i + 1 << ": ";
        cin >> sektor[i];

        cout << "Kebutuhan energi (kWh): ";
        cin >> kebutuhan[i];

        if (kebutuhan[i] < 0) {
            cout << "Data tidak valid, dilewati!\n";
            kebutuhan[i] = 0;
        }
    }
}

void case3() {

    if (total == 0 || jumlahSektor == 0) {
        cout << "Data energi atau sektor belum lengkap!\n";
        return;
    }

    double totalKebutuhan = 0;

    for (int i = 0; i < jumlahSektor; i++) {
        totalKebutuhan += kebutuhan[i];
    }

    double terpakai = (totalKebutuhan <= total) ? totalKebutuhan : total;
    double sisa = total - terpakai;

    double efisiensi = (terpakai / total) * 100;

    cout << "\n=== LAPORAN ENERGI ===\n";
    cout << "Total Energi      : " << total << " kWh\n";
    cout << "Energi Terpakai   : " << terpakai << " kWh\n";
    cout << "Energi Sisa       : " << sisa << " kWh\n";
    cout << "Efisiensi         : " << efisiensi << "%\n";

    if (efisiensi > 85) cout << "Status Energi     : Zona Aman\n";
    else if (efisiensi > 60) cout << "Status Energi     : Zona Waspada\n";
    else cout << "Status Energi     : Zona Penghematan\n";

    cout << "\nPersentase penggunaan tiap sektor:\n";

    for (int j = 0; j < jumlahSektor; j++) {
        double persen = (kebutuhan[j] / total) * 100;
        cout << sektor[j] << " : " << persen << "%\n";
    }
}

void case4() {
    cout << "Program selesai.\n";
    exit(0);
}

void case5() {

    if (jumlahSektor == 0) {
        cout << "Sektor belum diinput!\n";
        return;
    }

    cout << "\n=== PREDIKSI KEBUTUHAN ENERGI ===\n";

    for (int i = 0; i < jumlahSektor; i++) {
        double minggu = prediksiKebutuhan(kebutuhan[i], 1);
        double bulan = prediksiKebutuhan(kebutuhan[i], 2);

        cout << "\nSektor: " << sektor[i] << endl;
        cout << "Kebutuhan saat ini: " << kebutuhan[i] << " kWh\n";
        cout << "Prediksi 1 minggu : " << minggu << " kWh\n";
        cout << "Prediksi 1 bulan  : " << bulan << " kWh\n";
    }
}

void case6() {

    if (jumlahSektor == 0) {
        cout << "Sektor belum diinput!\n";
        return;
    }

    cout << "\n=== INPUT BIAYA ===\n";
    cout << "Biaya produksi per kWh: ";
    cin >> biayaProduksi;

    cout << "Biaya distribusi per kWh: ";
    cin >> biayaDistribusi;

    for (int i = 0; i < jumlahSektor; i++) {
        cout << "Pendapatan sektor " << sektor[i] << ": ";
        cin >> pendapatanSektor[i];

        tarifPerKwh[i] = biayaProduksi + biayaDistribusi;
        kategoriHarga[i] = kategoriTarif(tarifPerKwh[i], pendapatanSektor[i]);
    }

    cout << "\n=== LAPORAN TARIF ENERGI ===\n";

    for (int i = 0; i < jumlahSektor; i++) {
        cout << sektor[i] << " - Tarif: " << tarifPerKwh[i]
             << " | Kategori: " << kategoriHarga[i] << endl;
    }
}

void case7() {

    if (jumlahSektor == 0 || total == 0) {
        cout << "Data belum lengkap!\n";
        return;
    }

    double totalKebutuhan2 = 0;

    for (int i = 0; i < jumlahSektor; i++)
        totalKebutuhan2 += kebutuhan[i];

    cout << "Total energi tersedia: " << total << endl;
    cout << "Total kebutuhan:       " << totalKebutuhan2 << endl;

    if (totalKebutuhan2 <= total) {
        cout << "Energi cukup! Tidak perlu prioritas.\n";
        return;
    }

    cout << "\nEnergi kurang! Membuat prioritas...\n";

    for (int i = 0; i < jumlahSektor - 1; i++) {
        for (int j = i + 1; j < jumlahSektor; j++) {
            if (kebutuhan[i] > kebutuhan[j]) {
                swap(kebutuhan[i], kebutuhan[j]);
                swap(sektor[i], sektor[j]);
            }
        }
    }

    cout << "\n=== DAFTAR PRIORITAS ===\n";
    for (int i = 0; i < jumlahSektor; i++) {
        cout << i + 1 << ". " << sektor[i]
             << " (butuh " << kebutuhan[i] << " kWh)\n";
    }

    cout << "\nRekomendasi: Tambah produksi energi atau kurangi alokasi sektor bawah.\n";
}

int menu() {
    int pilih;
    cout << "\n=== MENU UTAMA ===\n";
    cout << "1. Input data energi\n";
    cout << "2. Input sektor & kebutuhan energi\n";
    cout << "3. Hitung efisiensi & laporan\n";
    cout << "4. Keluar\n";
    cout << "5. Prediksi kebutuhan energi sektor\n";
    cout << "6. Perhitungan biaya energi & keterjangkauan\n";
    cout << "7. Sistem prioritas distribusi energi\n";
    cout << "Pilih: ";
    cin >> pilih;
    return pilih;
}

int main() {

    int pilihan;

    judul();

    do {
        pilihan = menu();

        switch (pilihan) {

        case 1: case1(); break;
        case 2: case2(); break;
        case 3: case3(); break;
        case 4: case4(); break;
        case 5: case5(); break;
        case 6: case6(); break;
        case 7: case7(); break;

        default:
            cout << "Menu tidak valid!\n";
        }

    } while (true);

    return 0;
}
