#pragma once

// Excepciones de Iniciar Sessió / Esborrar Usuari
struct ErrorContrasenya {};
struct UsuariNoExisteix {};

// Excepciones de Registrar / Modificar
struct SobrenomExisteix {};
struct CorreuExisteix {};
struct MenorEdat {};