#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <map>
#include <set>
#include <list>
#include <set>
#include <unordered_set>

using namespace std;

class iPud
{
public:
    iPud() {}

    void addSong(string s, string a, int d)
    {
        if (canciones.count(s))
        {
            throw std::domain_error("ERROR addSong");
        }

        canciones[s] = {d};
    }

    void addToPlayList(string s)
    {
        if (canciones.count(s) == 0)
        {
            throw std::domain_error("ERROR addToPlayList");
        }
        if (!cancionesPlaylist.count(s))
        {
            auto it = playlist.insert(playlist.begin(), s);
            playlistTotalTime += canciones.at(*it).duracion;
            cancionesPlaylist.insert({s, it});
        }
    }

    string current()
    {
        if (playlist.size() == 0)
        {
            throw std::domain_error("ERROR current");
        }
        return playlist.front();
    }

    string play()
    {
        string s = "";
        if (!playlist.empty())
        {
            s = playlist.back();
            playlistTotalTime -= canciones.at(s).duracion;
            recientes.push_front(playlist.back());

            if (cancionesRecientes.count(s))
            {
                recientes.erase(cancionesRecientes.at(s));
            }

            cancionesRecientes[s] = recientes.begin();

            if (cancionesPlaylist.count(s))
            {
                cancionesPlaylist.erase(playlist.back());
            }
            playlist.pop_back();
        }
        else
        {
            throw std::domain_error("No hay canciones en la lista");
        }
        return s;
    }

    vector<string> recent(int &n)
    {
        vector<string> resultado;
        if (!recientes.empty())
        {
            auto i = recientes.begin();
            int j = 0;
            while (i != recientes.end() && j < n)
            {
                resultado.push_back(*i);
                i++;
                j++;
            }

            n = j;
        }
        else
        {
            throw std::domain_error("No hay canciones recientes");
        }

        return resultado;
    }

    void deleteSong(string s)
    {

        if (cancionesPlaylist.count(s))
        {
            playlistTotalTime -= canciones.at(s).duracion;

            auto it_playlist = cancionesPlaylist.at(s);
            playlist.erase(it_playlist);
            cancionesPlaylist.erase(s);
        }
        if (cancionesRecientes.count(s))
        {
            auto it_recientes = cancionesRecientes.at(s);
            recientes.erase(it_recientes);
            cancionesRecientes.erase(s);
        }
        if (canciones.count(s))
        {
            canciones.erase(s);
        }
    }

    int totalTime()
    {
        return playlistTotalTime;
    }

private:
    struct InfoCancion
    {
        int duracion;
    };

    unordered_map<string, list<string>::iterator> cancionesPlaylist;
    unordered_map<string, InfoCancion> canciones;
    unordered_map<string, list<string>::iterator> cancionesRecientes;
    list<string> recientes;
    list<string> playlist;
    int playlistTotalTime = 0;
};

bool tratar_caso()
{
    iPud f;
    string operacion;
    cin >> operacion;

    if (cin.eof())
        return false;

    while (operacion != "FIN")
    {
        try
        {
            if (operacion == "play")
            {
                string s;
                s = f.play();
                cout << "Sonando " << s << endl;
            }
            else if (operacion == "totalTime")
            {
                cout << "Tiempo total " << f.totalTime() << endl;
            }
            else if (operacion == "recent")
            {
                int n;
                cin >> n;
                vector<string> recent = f.recent(n);
                cout << "Las " << n << " mas recientes" << endl;
                for (auto i : recent)
                {
                    cout << "    " << i << endl;
                }
            }
            else if (operacion == "addSong")
            {
                string s;
                string a;
                int d;
                cin >> s >> a >> d;
                f.addSong(s, a, d);
            }
            else if (operacion == "addToPlaylist")
            {
                string s;
                cin >> s;
                f.addToPlayList(s);
            }
            else if (operacion == "deleteSong")
            {
                string s;
                cin >> s;
                f.deleteSong(s);
            }
            else if (operacion == "current")
            {
                string s;
                s = f.current();
                // cout << "Current " << s << endl;
            }
        }
        catch (exception &e)
        {
            cout << e.what() << "\n";
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("samples\\iPud_sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso())
    {
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Windows
    // system("PAUSE");
#endif
    return 0;
}