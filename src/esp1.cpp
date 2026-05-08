#include "iikit.h"

// --------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS — visíveis na aba "Variables" do debugger
// --------------------------------------------------------------------------

/** Conta quantas vezes updateAll() foi chamada. */
static uint32_t loopCount  = 0;

/** Leitura do Potenciômetro 1 (0 – 32767). */
static uint16_t pot1Value  = 0;

/** Leitura do Potenciômetro 2 (0 – 32767). */
static uint16_t pot2Value  = 0;

/** Estado atual do LED D1 (true = aceso). */
static bool ledD1State = false;

/** Estado atual do Relé (true = ativado). */
static bool releState  = false;

/**
 * @brief Lê os dois potenciômetros e armazena nos globais.
 *
 * Ponto de prática para Step Into:
 *   Pause em updateAll(), posicione o cursor em readSensors() e
 *   pressione F11 — você entrará aqui e verá pot1Value e pot2Value
 *   sendo preenchidos linha a linha.
 */
void readSensors() {
    pot1Value = IIKit.analogReadPot1();   // inspecione pot1Value após esta linha
    pot2Value = IIKit.analogReadPot2();   // inspecione pot2Value após esta linha
}

/**
 * @brief Calcula saídas: pisca LED e aciona relé conforme pot1Value.
 *
 * Ponto de prática para breakpoint condicional por valor:
 *   Coloque breakpoint na linha "releState = ..." e adicione a condição:
 *       pot1Value >= 16384
 *   O debugger pausará somente quando o potenciômetro passar de 50%.
 */
void processOutputs() {
    // LED alterna a cada 5 chamadas (~500 ms com período de 100 ms)
    if ((loopCount % 5) == 0) {
        ledD1State = !ledD1State;
        digitalWrite(def_pin_D1, ledD1State ? HIGH : LOW);
    }

    // Relé ativa quando pot1 ultrapassa 50% da escala (>= 16384 de 32767)
    releState = (pot1Value >= 16384);        // ← breakpoint condicional por valor aqui
    digitalWrite(def_pin_RELE, releState ? HIGH : LOW);
}

/**
 * @brief Atualiza o display OLED e envia dados para plot serial/UDP.
 *
 * Ponto de prática para Step Over:
 *   Pressione F10 nesta chamada para executar o driver todo de uma vez
 *   sem precisar entrar nos detalhes internos.
 */
void updateUI() {
    disp.setText(2, ("P1:" + String(pot1Value)).c_str());
    disp.setText(3, ("P2:" + String(pot2Value)).c_str());
    wserial.plot("pot1",      pot1Value);
    wserial.plot("pot2",      pot2Value);
    wserial.plot("loopCount", loopCount);
    wserial.plot("rele",      (uint8_t)releState);
}

void updateAll() {
    loopCount++;           // ← (a) breakpoint simples  (b) breakpoint por hit count
    readSensors();         // ← F11 Step Into  → inspeciona pot1Value / pot2Value
    processOutputs();      // ← F11 Step Into  → acompanha lógica LED e relé
    updateUI();            // ← F10 Step Over  → pula detalhes do driver
}

void setup() {
    IIKit.begin();
    disp.setText(1, "Debug Demo");
}

#define PERIOD_MS 100
static uint32_t lastMs = 0;

void loop() {
    IIKit.update();
    const uint32_t now = millis();
    if ((now - lastMs) >= PERIOD_MS) {
        lastMs = now;
        updateAll();   // ← ponto de entrada principal para breakpoints
    }
}