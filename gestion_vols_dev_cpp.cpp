#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// Fonctions de saisie compatibles avec Dev-C++ (C++98)
int lireInt(const string& message) {
    int valeur;
    cout << message;
    while (!(cin >> valeur)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entree invalide. Reessayez : ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valeur;
}

double lireDouble(const string& message) {
    double valeur;
    cout << message;
    while (!(cin >> valeur) || valeur < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valeur invalide. Reessayez : ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valeur;
}

string lireTexte(const string& message) {
    string valeur;
    cout << message;
    getline(cin, valeur);
    return valeur;
}

// ======================== CLASSE CLIENT ========================
class Client {
private:
    int idClient;
    string nom, prenom, telephone, email, passeport;

public:
    Client(int id, string n, string p, string t, string e, string pass) {
        idClient = id;
        nom = n;
        prenom = p;
        telephone = t;
        email = e;
        passeport = pass;
    }

    int getId() const {
        return idClient;
    }

    void afficherClient() const {
        cout << "\nID client : " << idClient
             << "\nNom : " << nom
             << "\nPrenom : " << prenom
             << "\nTelephone : " << telephone
             << "\nEmail : " << email
             << "\nPasseport : " << passeport << "\n";
    }
};

// ======================== CLASSE AGENT ========================
class Agent {
private:
    int idAgent;
    string nom, prenom, login, motDePasse;

public:
    Agent(int id, string n, string p, string l, string m) {
        idAgent = id;
        nom = n;
        prenom = p;
        login = l;
        motDePasse = m;
    }

    int getId() const {
        return idAgent;
    }

    void afficherAgent() const {
        cout << "\nID agent : " << idAgent
             << "\nNom : " << nom
             << "\nPrenom : " << prenom << "\n";
    }
};

// ==================== CLASSE ADMINISTRATEUR ====================
class Administrateur {
private:
    int idAdmin;
    string nom, login, motDePasse;

public:
    Administrateur(int id, string n, string l, string m) {
        idAdmin = id;
        nom = n;
        login = l;
        motDePasse = m;
    }

    void gererUtilisateurs() const {
        cout << "Gestion des utilisateurs.\n";
    }

    void gererVols() const {
        cout << "Gestion des vols.\n";
    }
};

// ========================= CLASSE VOL ==========================
class Vol {
private:
    int idVol;
    string numeroVol, origine, destination, dateDepart, heureDepart;
    double prix;
    int placesDisponibles;

public:
    Vol(int id, string numero, string origineVol, string destinationVol,
        string date, string heure, double prixVol, int places) {
        idVol = id;
        numeroVol = numero;
        origine = origineVol;
        destination = destinationVol;
        dateDepart = date;
        heureDepart = heure;
        prix = prixVol;
        placesDisponibles = places;
    }

    int getId() const {
        return idVol;
    }

    double getPrix() const {
        return prix;
    }

    bool reserverPlace() {
        if (placesDisponibles <= 0) {
            return false;
        }
        placesDisponibles--;
        return true;
    }

    void libererPlace() {
        placesDisponibles++;
    }

    void afficherVol() const {
        cout << "\nID vol : " << idVol
             << "\nNumero : " << numeroVol
             << "\nOrigine : " << origine
             << "\nDestination : " << destination
             << "\nDate de depart : " << dateDepart
             << "\nHeure de depart : " << heureDepart
             << "\nPrix : " << fixed << setprecision(2) << prix
             << "\nPlaces disponibles : " << placesDisponibles << "\n";
    }
};

// ====================== CLASSE RESERVATION =====================
class Reservation {
private:
    int idReservation, idClient, idVol, idAgent;
    string dateReservation, statut;
    double montantPaye;
    bool billetGenere;

public:
    Reservation(int id, int client, int vol, int agent, string date) {
        idReservation = id;
        idClient = client;
        idVol = vol;
        idAgent = agent;
        dateReservation = date;
        statut = "En attente de paiement";
        montantPaye = 0.0;
        billetGenere = false;
    }

    int getId() const {
        return idReservation;
    }

    int getIdVol() const {
        return idVol;
    }

    double getMontantPaye() const {
        return montantPaye;
    }

    string getStatut() const {
        return statut;
    }

    bool estAnnulee() const {
        return statut == "Annulee";
    }

    bool estBilletGenere() const {
        return billetGenere;
    }

    void ajouterPaiement(double montant) {
        montantPaye = montantPaye + montant;
    }

    void confirmer() {
        statut = "Confirmee";
    }

    void annuler() {
        statut = "Annulee";
    }

    void marquerBilletGenere() {
        billetGenere = true;
    }

    void afficherReservation() const {
        cout << "\nNumero reservation : " << idReservation
             << "\nID client : " << idClient
             << "\nID vol : " << idVol
             << "\nID agent : " << idAgent
             << "\nDate : " << dateReservation
             << "\nMontant paye : " << montantPaye
             << "\nStatut : " << statut << "\n";
    }
};

// ========================= CLASSE BILLET =======================
class Billet {
private:
    int idBillet, idReservation;
    double prix;

public:
    Billet(int id, int reservation, double prixBillet) {
        idBillet = id;
        idReservation = reservation;
        prix = prixBillet;
    }

    void imprimerBillet() const {
        cout << "\n====================================\n"
             << "             BILLET D'AVION\n"
             << "====================================\n"
             << "Numero billet : " << idBillet << "\n"
             << "Reservation : " << idReservation << "\n"
             << "Prix : " << fixed << setprecision(2) << prix << "\n"
             << "====================================\n";
    }
};

// ======================== CLASSE PAIEMENT ======================
class Paiement {
private:
    int idPaiement, idReservation;
    double montant;
    string datePaiement, modePaiement;

public:
    Paiement(int id, int reservation, double somme,
             string date, string mode) {
        idPaiement = id;
        idReservation = reservation;
        montant = somme;
        datePaiement = date;
        modePaiement = mode;
    }

    void afficherPaiement() const {
        cout << "\nID paiement : " << idPaiement
             << "\nReservation : " << idReservation
             << "\nMontant : " << montant
             << "\nDate : " << datePaiement
             << "\nMode : " << modePaiement << "\n";
    }
};

// =================== CLASSE AGENCE DE VOYAGE ===================
class AgenceVoyage {
private:
    vector<Client> clients;
    vector<Agent> agents;
    vector<Vol> vols;
    vector<Reservation> reservations;
    vector<Billet> billets;
    vector<Paiement> paiements;
    Administrateur administrateur;

    int prochainClient;
    int prochainVol;
    int prochaineReservation;
    int prochainBillet;
    int prochainPaiement;

    int rechercherVol(int id) const {
        int i;
        for (i = 0; i < (int)vols.size(); i++) {
            if (vols[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    int rechercherReservation(int id) const {
        int i;
        for (i = 0; i < (int)reservations.size(); i++) {
            if (reservations[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    bool clientExiste(int id) const {
        int i;
        for (i = 0; i < (int)clients.size(); i++) {
            if (clients[i].getId() == id) {
                return true;
            }
        }
        return false;
    }

public:
    AgenceVoyage()
        : administrateur(1, "Administrateur", "admin", "1234") {
        prochainClient = 1;
        prochainVol = 1;
        prochaineReservation = 1;
        prochainBillet = 1;
        prochainPaiement = 1;
        agents.push_back(Agent(1, "Agent", "Principal", "agent", "1234"));
    }

    void ajouterClient() {
        string nom = lireTexte("Nom : ");
        string prenom = lireTexte("Prenom : ");
        string telephone = lireTexte("Telephone : ");
        string email = lireTexte("Email : ");
        string passeport = lireTexte("Numero de passeport : ");

        clients.push_back(Client(prochainClient, nom, prenom,
                                 telephone, email, passeport));
        prochainClient++;
        cout << "Client ajoute avec succes.\n";
    }

    void ajouterVol() {
        string numero = lireTexte("Numero du vol : ");
        string origine = lireTexte("Ville de depart : ");
        string destination = lireTexte("Destination : ");
        string date = lireTexte("Date de depart : ");
        string heure = lireTexte("Heure de depart : ");
        double prix = lireDouble("Prix du billet : ");
        int places = lireInt("Nombre de places : ");

        if (places <= 0) {
            cout << "Le nombre de places doit etre positif.\n";
            return;
        }

        vols.push_back(Vol(prochainVol, numero, origine, destination,
                           date, heure, prix, places));
        prochainVol++;
        cout << "Vol ajoute avec succes.\n";
    }

    void afficherVols() const {
        int i;
        if (vols.empty()) {
            cout << "Aucun vol enregistre.\n";
            return;
        }
        for (i = 0; i < (int)vols.size(); i++) {
            vols[i].afficherVol();
        }
    }

    void effectuerReservation() {
        int idClient, idVol, indiceVol;
        string date;

        if (clients.empty() || vols.empty()) {
            cout << "Ajoutez d'abord au moins un client et un vol.\n";
            return;
        }

        cout << "\n--- Liste des clients ---\n";
        int i;
        for (i = 0; i < (int)clients.size(); i++) {
            clients[i].afficherClient();
        }

        idClient = lireInt("ID du client : ");
        if (!clientExiste(idClient)) {
            cout << "Client introuvable.\n";
            return;
        }

        cout << "\n--- Liste des vols ---\n";
        afficherVols();

        idVol = lireInt("ID du vol choisi : ");
        indiceVol = rechercherVol(idVol);
        if (indiceVol == -1) {
            cout << "Vol introuvable.\n";
            return;
        }

        if (!vols[indiceVol].reserverPlace()) {
            cout << "Aucune place disponible.\n";
            return;
        }

        date = lireTexte("Date de reservation : ");
        reservations.push_back(Reservation(prochaineReservation,
                                           idClient, idVol,
                                           agents[0].getId(), date));
        cout << "Reservation creee avec succes. Numero : "
             << prochaineReservation << "\n";
        prochaineReservation++;
    }

    void effectuerPaiement() {
        int id, indice, indiceVol;
        double montant, prix, reste;
        string date, mode;

        id = lireInt("Numero de reservation : ");
        indice = rechercherReservation(id);
        if (indice == -1) {
            cout << "Reservation introuvable.\n";
            return;
        }

        if (reservations[indice].estAnnulee()) {
            cout << "Cette reservation est annulee.\n";
            return;
        }

        if (reservations[indice].getStatut() == "Confirmee") {
            cout << "Cette reservation est deja payee.\n";
            return;
        }

        indiceVol = rechercherVol(reservations[indice].getIdVol());
        if (indiceVol == -1) {
            cout << "Vol associe introuvable.\n";
            return;
        }

        prix = vols[indiceVol].getPrix();
        reste = prix - reservations[indice].getMontantPaye();

        cout << "Prix total : " << prix
             << "\nMontant deja paye : "
             << reservations[indice].getMontantPaye()
             << "\nReste a payer : " << reste << "\n";

        montant = lireDouble("Montant a payer : ");
        if (montant <= 0 || montant > reste) {
            cout << "Montant invalide.\n";
            return;
        }

        date = lireTexte("Date du paiement : ");
        mode = lireTexte("Mode de paiement : ");

        paiements.push_back(Paiement(prochainPaiement, id,
                                     montant, date, mode));
        prochainPaiement++;

        reservations[indice].ajouterPaiement(montant);

        if (reservations[indice].getMontantPaye() >= prix) {
            reservations[indice].confirmer();
            cout << "Paiement complet. Reservation confirmee.\n";
        } else {
            cout << "Paiement partiel enregistre.\n";
        }
    }

    void genererBillet() {
        int id, indice, indiceVol;

        id = lireInt("Numero de reservation : ");
        indice = rechercherReservation(id);
        if (indice == -1) {
            cout << "Reservation introuvable.\n";
            return;
        }

        if (reservations[indice].estAnnulee() ||
            reservations[indice].getStatut() != "Confirmee") {
            cout << "La reservation doit etre payee integralement.\n";
            return;
        }

        if (reservations[indice].estBilletGenere()) {
            cout << "Un billet existe deja pour cette reservation.\n";
            return;
        }

        indiceVol = rechercherVol(reservations[indice].getIdVol());
        if (indiceVol == -1) {
            cout << "Vol introuvable.\n";
            return;
        }

        billets.push_back(Billet(prochainBillet, id,
                                 vols[indiceVol].getPrix()));
        prochainBillet++;
        reservations[indice].marquerBilletGenere();
        billets[billets.size() - 1].imprimerBillet();
    }

    void afficherReservations() const {
        int i;
        if (reservations.empty()) {
            cout << "Aucune reservation enregistree.\n";
            return;
        }
        for (i = 0; i < (int)reservations.size(); i++) {
            reservations[i].afficherReservation();
        }
    }

    void annulerReservation() {
        int id, indice, indiceVol;

        id = lireInt("Numero de reservation : ");
        indice = rechercherReservation(id);
        if (indice == -1) {
            cout << "Reservation introuvable.\n";
            return;
        }

        if (reservations[indice].estAnnulee()) {
            cout << "Cette reservation est deja annulee.\n";
            return;
        }

        indiceVol = rechercherVol(reservations[indice].getIdVol());
        if (indiceVol != -1) {
            vols[indiceVol].libererPlace();
        }

        reservations[indice].annuler();
        cout << "Reservation annulee. La place est liberee.\n";
        cout << "Le remboursement eventuel doit etre traite separement.\n";
    }

    void afficherPaiements() const {
        int i;
        if (paiements.empty()) {
            cout << "Aucun paiement enregistre.\n";
            return;
        }
        for (i = 0; i < (int)paiements.size(); i++) {
            paiements[i].afficherPaiement();
        }
    }

    void menu() {
        int choix;
        do {
            cout << "\n========================================\n"
                 << "       AGENCE DE VOYAGE - COTONOU\n"
                 << "  GESTION DES VOLS ET RESERVATIONS\n"
                 << "========================================\n"
                 << "1. Ajouter un client\n"
                 << "2. Ajouter un vol\n"
                 << "3. Consulter les vols\n"
                 << "4. Effectuer une reservation\n"
                 << "5. Enregistrer un paiement\n"
                 << "6. Generer un billet\n"
                 << "7. Consulter les reservations\n"
                 << "8. Annuler une reservation\n"
                 << "9. Consulter les paiements\n"
                 << "0. Quitter\n";

            choix = lireInt("Votre choix : ");

            switch (choix) {
                case 1: ajouterClient(); break;
                case 2: ajouterVol(); break;
                case 3: afficherVols(); break;
                case 4: effectuerReservation(); break;
                case 5: effectuerPaiement(); break;
                case 6: genererBillet(); break;
                case 7: afficherReservations(); break;
                case 8: annulerReservation(); break;
                case 9: afficherPaiements(); break;
                case 0: cout << "Fin du programme.\n"; break;
                default: cout << "Choix invalide.\n";
            }
        } while (choix != 0);
    }
};

// ============================= MAIN =============================
int main() {
    AgenceVoyage agence;
    agence.menu();
    return 0;
}
