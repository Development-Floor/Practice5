// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	start.X = 0;
	start.Y = 0;
	eventCount = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::move() {
	FVector2D Current = start;

	UE_LOG(LogTemp, Display, TEXT("(%d, %d) Distance: %f"), (int)(Current.X), (int)(Current.Y), distance(start, Current));

	// 제자리 걸음 방지용 변수
	int moveX = 0;
	int moveY = 0;

	// 이벤트 연속 발생x
	bool checkEvent = true;

	for (int i = 0; i < 10; i++) {
		if (checkEvent && FMath::RandRange(0, 1) && !(Current.X == 0 && Current.Y == 0)) {
			event(Current);
			i--;
			UE_LOG(LogTemp, Error, TEXT("Event! => (%d, %d) Distance: %f"), (int)(Current.X), (int)(Current.Y), distance(start, Current));
			checkEvent = false;
			continue;
		}

		checkEvent = true;

		do {
			moveX = step();
			moveY = step();
		} while (moveX == 0 && moveY == 0);

		Current.X += moveX;
		Current.Y += moveY;

		UE_LOG(LogTemp, Display, TEXT("(%d, %d) Distance: %f"), (int)(Current.X), (int)(Current.Y), distance(start, Current));
	}

	UE_LOG(LogTemp, Warning, TEXT("EventCount: %d, Distance: %f"), eventCount, distance(start, Current));
}

int AMyActor::step() {
	return FMath::RandRange(-1, 1);
}

float AMyActor::distance(FVector2D first, FVector2D second) {
	return sqrt(pow(first.X - second.X, 2) + pow(first.Y - second.Y, 2));
}

void AMyActor::event(FVector2D& Current) {
	eventCount++;

	int num = FMath::RandRange(0, 3);

	FVector2D temp = Current;

	if (num == 0) {
		Current.X = -Current.X;
	}
	else if (num == 1) {
		Current.Y = -Current.Y;
	}
	else if (num == 2) {
		Current.X = -Current.X;
		Current.Y = -Current.Y;
	}
	else if (num == 3) {
		Swap(Current.X, Current.Y);
	}

	if (temp.X == Current.X && temp.Y == Current.Y) {
		eventCount--;
		event(Current);
	}
}

