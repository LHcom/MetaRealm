# 🏢 MetaRealm

> **3D 공간에서 실시간 회의·요약이 가능한 메타버스 오피스**

---

## ✅ 프로젝트 소개

**MetaRealm**은 Unreal Engine 기반의 **시공간 제약 없는 3D 메타 오피스** 프로젝트입니다.  
사용자는 3D 공간에서 회의실·게시판·대화 기능을 통해 언제 어디서든 원격 협업이 가능합니다.

- **장르**: 메타오피스 / 시뮬레이션  
- **개발 기간**: 2024.08.23 ~ 2024.09.27 (5주)  
- **인원 구성**: 8명 (개발 4, BA 3, AI 1)

---

## 🔧 주요 기능

- 🔗 **Listen Server 멀티플레이**  
  OnlineSubsystemSteam 기반의 Listen Server 구성 및 세션 탐색/생성/참여 처리  

- 🧑‍💻 **REST API 통신**  
  회원가입·로그인·회의록 요청을 JSON/POST 방식으로 외부 서버에 전달 및 응답 처리  

- 🗣 **회의 요약 기능**  
  녹음된 음성 파일을 AI 서버에 전송 → 요약 결과 수신 → Data Asset에 저장  

- 📁 **상태 저장 기능**  
  회의실/게시판 정보를 Data Asset에 저장 및 로딩, 클라이언트에 Replicate  

- 🖥 **UI 시스템**  
  로그인, 회의실, 게시판, 요약 결과 등 다양한 사용자 인터페이스 구현

- 🌐 **Pixel Streaming**  
  고사양 PC 없이도 웹 브라우저에서 **메타버스 환경 실시간 접속** 가능

---

## 🛠 기술 스택

- **Engine**: Unreal Engine 5.4  
- **Language**: C++, Blueprint  
- **Network**: Listen Server (OnlineSubsystemSteam), Pixel Streaming  
- **API 통신**: REST API (GET, POST, JSON)  
- **데이터 관리**: Data Asset / 외부 Database  
- **협업 방식**: Git + 기능 기반 폴더 구조 분리

---

## 🧩 프로젝트 구조

### 🔐 로그인 및 세션 흐름
- 로그인 요청 시 JSON으로 서버 통신  
- 세션 탐색 후 없으면 생성 / 있으면 참가  
- GameState에 플레이어 정보 등록 및 UI 갱신

<img width="1015" height="441" alt="Image" src="https://github.com/user-attachments/assets/689753f5-8d51-452a-afbb-eaba973ff504" />

### 📝 게시판 공유
- 게시판 내용 작성 후 Server RPC 처리  
- GameState에 저장 후 Replicate로 클라이언트 동기화

<img width="841" height="331" alt="Image" src="https://github.com/user-attachments/assets/13634b0f-b30f-494c-ba3c-23e72c74b8eb" />

### 🗣 회의 요약 처리
- 회의 음성 파일 전송 → AI 서버 요약  
- GameState에 저장 및 요약 UI로 출력

<img width="841" height="432" alt="Image" src="https://github.com/user-attachments/assets/899b7af6-eea5-4d5f-b4d0-05f53eaab54b" />

---

## 👥 팀 구성 및 역할

| 역할 | 담당 내용 |
|---|---|
| **XR (팀장)** | 세션/로그인/회원가입, REST API 연동, DataAsset 설계, DB 설계 |
| XR | 캐릭터 커스터마이징, 채팅 시스템, 레벨 구성 |
| XR | 회의 음성 녹음, 서버 전송, UI 구현 |
| XR | Pixel Streaming 환경 구성, Application 화면 스트리밍 |
| BA | API 인증(Spring Security + JWT), DB 구축 |
| AI | STT 및 요약 분석 처리, 생성형 AI 연동 |

---

## 📈 성과 요약

- 실시간 멀티 유저 접속 및 회의 지원 구조 완성
- REST API → JSON 파싱 → 저장 → UI 연동 전 흐름 개발
- 음성 기반 회의 요약 자동화 기능 탑재
- 게시판 및 회의실 정보의 저장 및 복원 기능 구현
- Pixel Streaming을 통한 **스트리밍** 지원
