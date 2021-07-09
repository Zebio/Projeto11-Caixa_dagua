#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


#define SERVICE_UUID "a27bef92-590a-4817-8359-57c6966bfe51"
#define CAIXA_VAZIA_UUID "a27bef92-590a-4817-8359-57c6966bfe52"
#define CAIXA_CHEIA_UUID "a27bef92-590a-4817-8359-57c6966bfe53"

BLEServer * server = NULL;
BLECharacteristic *caixa_vazia =NULL;
BLECharacteristic *caixa_cheia =NULL;


void leitura()
{
  float valor_caixa_vazia;
  valor_caixa_vazia=0;
  float valor_caixa_cheia;
  valor_caixa_cheia=1;

  caixa_vazia->setValue(valor_caixa_vazia);
  caixa_vazia->notify();
  caixa_cheia->setValue(valor_caixa_cheia);
  caixa_cheia->notify();

}

void setup() 
{
  BLEDevice::init("CaixaDagua");
  server=BLEDevice::createServer();
  //configurar callbacks
  BLEService *service = server->createService(SERVICE_UUID);
  
  //configurar características
  caixa_vazia = service->createCharacteristic(
    CAIXA_VAZIA_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY
    );

    caixa_cheia = service->createCharacteristic(
    CAIXA_CHEIA_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY
    );


  //inicializar serviço
  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(false);
  advertising->setMinPreferred(0x06);

  BLEDevice::startAdvertising();
}

void loop() {
  leitura();
}

