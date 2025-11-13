#pragma once
class GuardarPartida
{
private:
    //ATRIBUTOS PARA GUARDAR LOS DATOS DE CADA PARTE DEL JUEGO
    //PERSONAJE
        float pjX, pjY;           
        float pjVelocidadX, pjVelocidadY; 
    //ENEMIGO
        float enemigoX, enemigoY;
        float enemigoDirX, enemigoDirY; 
        float enemigoVelocidad;
    //ITEMS
        float itemX, itemY;           
        float itemPowerUpX, itemPowerUpY; 
    //ESTADO DEL JUEGO
        int puntuacion;
        int muertes;
        int timerPowerUp;
        bool gameOver;

public:
        GuardarPartida();

    //SETTERS PARA GUARDAR DATOS EN EL OBJETO DESDE EL JUEGO       
        void setDatosPersonaje(float x, float y, float velX, float velY);
        void setDatosEnemigo(float x, float y, float dirX, float dirY, float vel);
        void setDatosItemNormal(float x, float y);
        void setDatosItemPowerUp(float x, float y);
        void setEstadoJuego(int pts, int mts, int timer, bool gameOver);

    //GETTERS PARA GUARDAR DATOS EN EL OBJETO DESDE EL JUEGO
        void getDatosPersonaje(float& x, float& y, float& velX, float& velY);
        void getDatosEnemigo(float& x, float& y, float& dirX, float& dirY, float& vel);
        void getDatosItemNormal(float& x, float& y);
        void getDatosItemPowerUp(float& x, float& y);
        void getEstadoJuego(int& pts, int& mts, int& timer, bool& gameOver);

        //METODO PARA VALIDAR LOS DATOS GUARDADOS (SIN IMPLEMENTACION POR AHORA)
        //bool esValida();
    };
