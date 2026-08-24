# Assignment7 - UE5 Module & Plugin

## 개발 환경

* Unreal Engine 5.5.4
* C++

---

# 1. 새로운 Test 모듈 생성

기존 `Assignment7` 게임 모듈과 별도로 동작하는 `Test` 모듈을 생성했습니다.

## 폴더 구조

`Source/Test` 경로를 생성하고 모듈에 필요한 기본 파일을 구성했습니다.

```text
Source/
├── Assignment7/
│   ├── Assignment7.Build.cs
│   ├── Assignment7.cpp
│   ├── Assignment7.h
│   └── ...
│
└── Test/
    ├── Test.Build.cs
    ├── Test.h
    ├── Test.cpp
    ├── TestActor.h
    └── TestActor.cpp
```

`Test` 모듈에는 기본 모듈 파일인 `Test.Build.cs`, `Test.h`, `Test.cpp`를 작성하고, 모듈 간 상호작용을 확인하기 위해 `TestActor` 클래스도 추가했습니다.

---

# 2. Test.Build.cs 설정

`Test.Build.cs`에서 모듈이 사용할 Unreal Engine 모듈을 지정했습니다.

```cpp
PublicDependencyModuleNames.AddRange(new string[]
{
    "Core",
    "Engine"
});
```

### Dependency(종속성)

* **Public Dependency**

  * 해당 모듈의 헤더와 소스에서 필요한 모듈
* **Private Dependency**

  * 해당 모듈의 `.cpp`에서만 필요한 모듈

이번 `Test` 모듈에서는 `Core`, `Engine`을 Public Dependency로 등록했습니다.

---

# 3. Test 모듈 구현

`Test.cpp`에서는 일반적인 Unreal Engine 모듈 형태로 모듈을 구현했습니다.

```cpp
#include "Test.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, Test);
```

`IMPLEMENT_MODULE` 매크로를 사용하여 Unreal Engine이 `Test` 모듈을 정상적으로 로드할 수 있도록 구성했습니다.

`FDefaultModuleImpl`은 별도의 초기화 및 종료 로직이 필요하지 않은 일반적인 모듈에서 사용할 수 있는 기본 모듈 구현입니다.

---

# 4. Build Target에 Test 모듈 등록

새롭게 생성한 `Test` 모듈이 실제 빌드 과정에 포함되도록 Target 파일을 수정했습니다.

수정한 파일:

```text
Source/Assignment7.Target.cs
Source/Assignment7Editor.Target.cs
```

각 Target의 `ExtraModuleNames`에 `Test`를 추가했습니다.

```cpp
ExtraModuleNames.Add("Assignment7");
ExtraModuleNames.Add("Test");
```

이를 통해 게임 빌드와 에디터 빌드에서 `Test` 모듈이 함께 빌드되도록 설정했습니다.

---

# 5. Assignment7.uproject에 Test 모듈 등록

프로젝트가 `Test` 모듈을 인식할 수 있도록 `Assignment7.uproject`의 `Modules` 항목에 `Test`를 추가했습니다.

```json
{
    "Name": "Test",
    "Type": "Runtime",
    "LoadingPhase": "PreDefault",
    "AdditionalDependencies": [
        "Engine"
    ]
}
```

`LoadingPhase`는 `PreDefault`로 설정했습니다.

현재 프로젝트의 `Assignment7.uproject`에는 `Assignment7`과 `Test` 두 개의 Runtime 모듈이 등록되어 있습니다.

---

# 6. Visual Studio 프로젝트 파일 재생성

모듈을 새로 추가한 이후 기존 Visual Studio 솔루션에 `Test` 모듈이 정상적으로 표시되도록 프로젝트 파일을 다시 생성했습니다.

프로젝트의 `.uproject` 파일을 우클릭하여:

```text
Generate Visual Studio project files
```

를 실행했습니다.

이 과정을 통해 Unreal Engine 프로젝트와 Visual Studio의 프로젝트 정보를 갱신했습니다.

---

# 7. TestActor 생성

`Test` 모듈이 실제 게임 모듈에서 사용되는지 확인하기 위해 `TestActor` 클래스를 생성했습니다.

```text
Source/Test/
├── TestActor.h
└── TestActor.cpp
```

`TestActor`는 `AActor`를 상속받도록 구현했습니다.

`BeginPlay()`에서는 모듈이 정상적으로 동작하는지 확인할 수 있도록 로그와 화면의 메시지를 출력하도록 구현했습니다.

```cpp
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("TestActor BeginPlay!"));

	GEngine->AddOnScreenDebugMessage(
		-1,
		5.0f,
		FColor::Red,
		TEXT("TestActor BeginPlay!")
	);
}
```

---

# 8. 모듈 간 상호작용 구현

새롭게 생성한 `Test` 모듈의 `TestActor`를 기존 `Assignment7` 모듈에서 사용했습니다.

기존 게임 모듈의 캐릭터에서 `TestActor.h`를 Include하고 `SpawnActor`를 이용하여 `TestActor`를 생성했습니다.

```cpp
#include "TestActor.h"
```

그리고 `BeginPlay()`에서 다음과 같이 Actor를 Spawn했습니다.

```cpp
ATestActor* TestActor = GetWorld()->SpawnActor<ATestActor>(
    ATestActor::StaticClass(),
    GetActorLocation(),
    GetActorRotation()
);
```

이를 통해 다음과 같은 모듈 간 관계를 확인했습니다.

```text
Assignment7 Module
       │
       │ TestActor 참조
       ▼
   Test Module
       │
       ▼
   TestActor
```

즉, 기존 게임 모듈에서 별도로 생성한 `Test` 모듈의 클래스를 참조하고 실행할 수 있도록 구성했습니다.

---

# 9. 독립 Plugin(플러그인) 생성

모듈 구성에 이어 Unreal Engine의 Plugin 구조를 직접 만들어보기 위해 `Temporary`라는 독립 플러그인을 생성했습니다.

프로젝트 내부에 다음과 같은 구조를 구성했습니다.

```text
Plugins/
└── Temporary/
    ├── Content/
    ├── Source/
    │   └── Temporary/
    │       ├── Private/
    │       │   └── Temporary.cpp
    │       ├── Public/
    │       │   └── Temporary.h
    │       └── Temporary.Build.cs
    │
    └── Temporary.uplugin
```

GitHub 저장소에서도 `Plugins/Temporary` 아래에 `Resources`, `Source/Temporary`, `Temporary.uplugin`이 구성되어 있습니다.

---

# 10. Temporary.uplugin 설정

`Temporary.uplugin` 파일을 생성하여 플러그인의 기본 정보와 모듈 정보를 정의했습니다.

플러그인 내부에서 사용할 `Temporary` 모듈을 Runtime 모듈로 등록했습니다.

```json
{
    "FileVersion": 3,
    "Version": 1,
    "VersionName": "1.0",
    "FriendlyName": "Temporary",
    "Description": "Temporary Plugin",
    "Category": "Other",
    "Modules": [
        {
            "Name": "Temporary",
            "Type": "Runtime",
            "LoadingPhase": "Default"
        }
    ]
}
```

`.uplugin` 파일은 플러그인의 메타데이터와 어떤 모듈을 포함하고 있는지를 Unreal Engine에 알려주는 역할을 합니다.

---

# 11. Temporary 모듈 구성

플러그인 내부에도 별도의 Unreal Engine Module을 구성했습니다.

```text
Plugins/Temporary/Source/Temporary/
├── Private/
├── Public/
└── Temporary.Build.cs
```

`Temporary.Build.cs`에서 플러그인 모듈이 사용할 Unreal Engine 모듈을 설정했습니다.

```cpp
PublicDependencyModuleNames.AddRange(new string[]
{
    "Core"
});
```

---

# 12. StartupModule / ShutdownModule 구현

플러그인 모듈의 초기화와 종료 시점을 확인하기 위해 `StartupModule()`과 `ShutdownModule()`을 구현했습니다.

```cpp
class FTemporaryModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
```

그리고 `.cpp`에서 다음과 같이 구현했습니다.

```cpp
void FTemporaryModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("Temporary Plugin Started"));
}

void FTemporaryModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("Temporary Plugin Shutdown"));
}
```

`StartupModule()`은 플러그인이 로드될 때 호출되고, `ShutdownModule()`은 플러그인이 종료되거나 언로드될 때 호출됩니다.

---

# 13. 플러그인 활성화

프로젝트에서 `Temporary` 플러그인을 사용할 수 있도록 `Assignment7.uproject`의 `Plugins` 항목에 등록했습니다.

```json
{
    "Name": "Temporary",
    "Enabled": true
}
```

현재 프로젝트 파일에서도 `Temporary` 플러그인이 `Enabled: true`로 등록되어 있습니다.

---

# 14. 최종 구조

최종적으로 프로젝트는 게임 모듈, 별도의 `Test` 모듈, 독립적인 `Temporary` 플러그인을 포함하는 형태로 구성했습니다.

```text
Assignment7/
│
├── Assignment7.uproject
│
├── Source/
│   ├── Assignment7/
│   │   └── 기존 게임 모듈
│   │
│   └── Test/
│       ├── Test.Build.cs
│       ├── Test.h
│       ├── Test.cpp
│       ├── TestActor.h
│       └── TestActor.cpp
│
└── Plugins/
    └── Temporary/
        ├── Resources/
        ├── Source/
        │   └── Temporary/
        │       ├── Private/
        │       ├── Public/
        │       └── Temporary.Build.cs
        │
        └── Temporary.uplugin
```

---

# 15. 실행 및 검증

최종적으로 프로젝트를 빌드하고 Unreal Editor를 실행하여 다음 사항을 확인했습니다.

### Test Module

* `Test` 모듈이 정상적으로 빌드되는지 확인
* `TestActor`가 정상적으로 Spawn되는지 확인
* `BeginPlay()`의 로그가 출력되는지 확인
* 기존 `Assignment7` 모듈에서 `Test` 모듈의 클래스를 정상적으로 참조하는지 확인

### Temporary Plugin

* `Temporary` 플러그인이 프로젝트에서 활성화되는지 확인
* 플러그인의 Module이 정상적으로 로드되는지 확인
* `StartupModule()`과 `ShutdownModule()`이 정상적으로 동작하는지 확인
* Unreal Editor에서 플러그인 구조가 정상적으로 인식되는지 확인

---

# 16. 정리

이번 과제를 통해 Unreal Engine에서 **Module(모듈)**과 **Plugin(플러그인)**의 구조와 연결 방법을 직접 구현했습니다.

먼저 `Source/Test`에 새로운 모듈을 생성하고 `Build.cs`에서 Dependency(종속성)를 설정했습니다. 이후 Target.cs와 `.uproject`에 모듈을 등록하여 실제 빌드 과정에 포함시켰습니다.

또한 `TestActor`를 별도 모듈에 구현하고 기존 `Assignment7` 모듈에서 `SpawnActor`로 생성함으로써 **모듈 간 상호작용**을 확인했습니다.

마지막으로 `Plugins/Temporary` 경로에 `.uplugin` 파일과 별도의 Module을 직접 구성하여 Unreal Engine의 **독립적인 Plugin 구조**를 만들어 보았습니다.

이를 통해 Unreal Engine 프로젝트에서 기능을 모듈 단위로 분리하고, 재사용 가능한 Plugin 형태로 확장할 수 있는 기본 구조를 학습했습니다.
