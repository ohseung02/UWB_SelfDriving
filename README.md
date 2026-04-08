# 🛰️ UWB 통신 차량을 이용한 자동 배송 시스템 (Autonomous Delivery System using UWB)

이 프로젝트는 **UWB(Ultra-Wideband) 통신 기술**을 활용하여 정밀한 위치 측정을 기반으로 하는 **자동 배송 차량 시스템**의 구현 사례입니다.

---

## 🛠️ 주요 구성 및 기술 (Key Technologies)

- **하드웨어:** Arduino, UWB Sensor (DW1000 등), Motor Driver, GPS 등
- **주요 기능:**
  - **UWB 기반 정밀 거리 측정:** Tag와 Anchor 사이의 거리를 실시간으로 측정하여 위치 파악.
  - **자율 주행 알고리즘:** 측정된 거리 데이터를 바탕으로 지정된 위치까지 주행.
  - **송수신(Sender/Receiver) 통신:** 데이터 송수신을 통한 차량 제어.

---

## 📂 폴더 구조 (Project Structure)

- `src/`: 아두이노 소스 코드 (Sender, Receiver 최종본)
- `docs/`: 프로젝트 발표 자료, 기술 설명서 및 포스터 (PDF, PPTX)
- `media/`: 시스템 구동 영상 (MP4)

---

## 🚀 시작하기 (How to Use)

1. `src/sender`와 `src/receiver` 폴더의 코드를 각각의 아두이노 보드에 업로드합니다.
2. `docs/` 폴더의 포스터 및 발표 자료를 통해 하드웨어 결선도와 시스템 설계를 확인하세요.
3. `media/` 폴더에서 실제 동작 영상을 확인하실 수 있습니다.

---

## 🎓 학술 정보 (Academic Information)

- **과목명:** 캡스톤 디자인 (공학설계)
- **제작 시기:** 2025년 (3학년 6학기)

---

### 📄 관련 문서 및 자료
- **발표 자료:** `docs/[공학설계]K조, N조 발표자료.pptx`
- **포스터:** `docs/[포스터] UWB 통신 차량을 이용한 자동 배송 시스템.pdf`
