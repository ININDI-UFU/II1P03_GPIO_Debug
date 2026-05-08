/**
 * @file esp0.cpp
 * @brief Exemplo didático para praticar técnicas de debug no VS Code / PlatformIO.
 *        Usa os drivers diretamente (sem iikit.h / wserial).
 *        Saída de dados: Serial (monitor serial ou plot via ">var:ts:val").
 *
 * ==========================================================================
 * GUIA RÁPIDO DE DEBUG
 * ==========================================================================
 *
 * 1. STEP INTO (F11)
 *    Pause em updateAll() e pressione F11 sobre readSensors() para
 *    entrar e ver pot1Value / pot2Value sendo lidos linha a linha.
 *
 * 2. STEP OVER (F10)
 *    Pause em updateAll() e pressione F10 sobre updateUI() para
 *    executar o bloco de display/Serial sem entrar nos detalhes.
 *
 * 3. BREAKPOINT CONDICIONAL — por número de vezes (Hit Count)
 *    Clique com botão direito no breakpoint de "loopCount++"
 *    → "Edit Breakpoint..." → "Hit Count" → informe 10.
 *    O debugger pausará somente na 10ª chamada.
 *
 * 4. BREAKPOINT CONDICIONAL — por valor de variável (Expression)
 *    Clique com botão direito no breakpoint de "releState = ..."
 *    → "Edit Breakpoint..." → "Expression" → informe:
 *        pot1Value >= 16384
 *    O debugger pausará somente quando o POT ultrapassar 50%.
 * ==========================================================================
 */

#include <Arduino.h>
#include "services/ads1115.h"         // ads1115  — ADS1115 ADC externo
#include "services/display_ssd1306.h" // disp     — display OLED SSD1306
#include "util/lasecGPIOKit.h"        // def_pin_* — só as constantes de pino

// --------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS — visíveis na aba "Variables" do debugger
// --------------------------------------------------------------------------

/** Conta quantas vezes updateAll() foi chamada.
 *  Use "Hit Count" nesta variável para parar na iteração N. */
static uint32_t loopCount = 0;

/** Leitura do Potenciômetro 1 (0 – 32767).
 *  Use "Expression: pot1Value >= 16384" para parar ao ultrapassar 50%. */
static uint16_t pot1Value = 0;

/** Leitura do Potenciômetro 2 (0 – 32767). */
static uint16_t pot2Value = 0;

/** Estado atual do LED D1 (true = aceso). */
static bool ledD1State = false;

/** Estado atual do Relé (true = ativado). */
static bool releState = false;

// --------------------------------------------------------------------------
// FUNÇÕES AUXILIARES
// Use Step Into (F11) para entrar; Step Over (F10) para pular.
// --------------------------------------------------------------------------

/**
 * @brief Lê os dois potenciômetros e armazena nos globais.
 *
 * Ponto de prática para Step Into (F11):
 *   Pause em updateAll() → pressione F11 sobre readSensors() →
 *   você entrará aqui e verá pot1Value e pot2Value sendo preenchidos.
 */
void readSensors() {
    pot1Value = ads1115.analogReadPot1();  // inspecione pot1Value após esta linha
    pot2Value = ads1115.analogReadPot2();  // inspecione pot2Value após esta linha
}

/**
 * @brief Calcula saídas: pisca LED D1 e aciona Relé conforme pot1Value.
 *
 * Ponto de prática para breakpoint condicional por valor (Expression):
 *   Coloque breakpoint na linha "releState = ..." e adicione:
 *       pot1Value >= 16384
 */
void processOutputs() {
    // LED alterna a cada 5 chamadas (~500 ms com PERIOD_MS = 100)
    if ((loopCount % 5) == 0) {
        ledD1State = !ledD1State;
        digitalWrite(def_pin_D1, ledD1State ? HIGH : LOW);
    }

    // Relé ativa quando pot1 ultrapassa 50% da escala (0–32767)
    releState = (pot1Value >= 16384);           // ← breakpoint condicional por valor aqui
    digitalWrite(def_pin_RELE, releState ? HIGH : LOW);
}

/**
 * @brief Atualiza o display OLED e envia dados para o monitor serial.
 *
 * Saída no formato Serial Plotter do Arduino / VS Code:
 *   >varName:timestamp_ms:valor
 *
 * Ponto de prática para Step Over (F10):
 *   Pressione F10 sobre updateUI() para executar sem entrar nos detalhes.
 */
void updateUI() {
    // Display OLED — linha 2 e 3
    disp.setText(2, ("P1:" + String(pot1Value)).c_str());
    disp.setText(3, ("P2:" + String(pot2Value)).c_str());
    disp.update();

    // Saída serial no formato ">var:ts:val" (compatível com Serial Plotter)
    uint32_t ts = millis();
    Serial.printf(">pot1:%lu:%u\r\n",      ts, pot1Value);
    Serial.printf(">pot2:%lu:%u\r\n",      ts, pot2Value);
    Serial.printf(">loopCount:%lu:%lu\r\n", ts, loopCount);
    Serial.printf(">rele:%lu:%u\r\n",      ts, (uint8_t)releState);
}

void updateAll() {
    loopCount++;          // ← (a) breakpoint simples  (b) breakpoint por hit count
    readSensors();        // ← F11 Step Into  → inspeciona pot1Value / pot2Value
    processOutputs();     // ← F11 Step Into  → acompanha lógica LED e relé
    updateUI();           // ← F10 Step Over  → pula detalhes de display e Serial
}

void setup() {
    Serial.begin(115200);

    // Display OLED
    if (!disp.begin(def_pin_SDA, def_pin_SCL)) {
        Serial.println("Erro: display nao inicializado!");
    }
    disp.setText(1, "Debug Demo");
    disp.update();

    // ADC externo ADS1115
    if (!ads1115.begin()) {
        Serial.println("Erro: ADS1115 nao encontrado!");
    }

    // Pinos de saída — mesma configuração de lasecGPIOKit::begin()
    pinMode(def_pin_D1,   OUTPUT);  digitalWrite(def_pin_D1,   LOW);
    pinMode(def_pin_RELE, OUTPUT);  digitalWrite(def_pin_RELE, LOW);
}

#define PERIOD_MS 100
static uint32_t lastMs = 0;

void loop() {
    const uint32_t now = millis();
    if ((now - lastMs) >= PERIOD_MS) {
        lastMs = now;
        updateAll();  // ← ponto de entrada principal para breakpoints
    }
}