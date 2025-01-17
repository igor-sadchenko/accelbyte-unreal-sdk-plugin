// Copyright (c) 2020 AccelByte Inc. All Rights Reserved.
// This is licensed software from AccelByte Inc, for limitations
// and restrictions contact your company contract manager.

#pragma once

#include "CoreMinimal.h"
#include "Core/AccelByteError.h"
#include "Models/AccelByteEcommerceModels.h"
#include "Core/AccelByteHttpRetryScheduler.h"
#include "Core/AccelByteServerApiBase.h"

namespace AccelByte
{
class ServerCredentials;
class ServerSettings;
namespace GameServerApi
{

/**
* @brief Ecommerce API to manage user's Ecommerce related things like Entitlement and Wallet.
*/
class ACCELBYTEUE4SDK_API ServerEcommerce : public FServerApiBase
{
public:
	ServerEcommerce(ServerCredentials const& InCredentialsRef, ServerSettings const& InSettingsRef, FHttpRetryScheduler& InHttpRef);
	~ServerEcommerce();

	/**
	 * @brief Get list of user's Entitlement(s).
	 *
	 * @param UserId The user id who have the entitlements
	 * @param bActiveOnly Set as true if you want to search the active only, and vice-versa.
	 * @param EntitlementName The name of the entitlement (optional).
	 * @param ItemIds Item's id (optional).
	 * @param Offset Offset of the list that has been sliced based on Limit parameter (optional, default = 0).
	 * @param Limit The limit of item on page (optional).
	 * @param OnSuccess This will be called when the operation success. The result is const FAccelByteModelsEntitlementPagingSlicedResult.
	 * @param OnError This will be called when the operation failed.
	 * @param EntitlementClass Class of the entitlement (optional).
	 * @param AppType This is the type of application that entitled (optional).
	 * @param Features (optional).
	 */
	void QueryUserEntitlements(const FString& UserId
		, bool bActiveOnly
		, const FString& EntitlementName
		, const TArray<FString>& ItemIds
		, const int32& Offset
		, const int32& Limit
		, const THandler<FAccelByteModelsEntitlementPagingSlicedResult>& OnSuccess
		, const FErrorHandler& OnError
		, EAccelByteEntitlementClass EntitlementClass = EAccelByteEntitlementClass::NONE
		, EAccelByteAppType AppType = EAccelByteAppType::NONE
		, const TArray<FString>& Features = {});

	/**
	 * @brief Get Entitlement's Info by the EntitlementId.
	 *
	 * @param EntitlementId The id of the entitlement.
	 * @param OnSuccess This will be called when the operation success. The result is const FAccelByteModelsEntitlementInfo.
	 * @param OnError This will be called when the operation failed.
	 */
	void GetUserEntitlementById(const FString& EntitlementId
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Get Entitlement info by the UserId and EntitlementId
	 *
	 * @param UserId The user id who have the entitlements
	 * @param EntitlementId The id of the entitlement
	 * @param OnSuccess This will be called when the operation success. The result is const FAccelByteModelsEntitlementInfo.
	 * @param OnError This will be called when the operation failed.
	 */
	void GetUserEntitlementById(const FString& UserId
		, const FString& EntitlementId
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError);
	
	/**
	 * @brief Granting Entitlement(s) to a user.
	 *
	 * @param UserId The user who will get the entilement(s).
	 * @param EntitlementGrant Consist of the entitlement(s) that will be granted.
	 * @param OnSuccess This will be called when the operation succeeded. The result is an array of FAccelByteModelsStackableEntitlementInfo.
	 * @param OnError This will be called when the operation failed.
	 */
	void GrantUserEntitlements(const FString& UserId
		, const TArray<FAccelByteModelsEntitlementGrant>& EntitlementGrant
		, const THandler<TArray<FAccelByteModelsStackableEntitlementInfo>>& OnSuccess
		, const FErrorHandler& OnError);
	
	/**
	 * @brief Credit a user wallet by currency code, if the wallet does not exist, it will create a new wallet.
	 *
	 * @param UserId The user who will receive credit.
	 * @param CurrencyCode The currency code.
	 * @param CreditUserWalletRequest The request to credit a user wallet.
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsWalletInfo&.
	 * @param OnError This will be called when the operation fails.
	 */
	void CreditUserWallet(const FString& UserId
		, const FString& CurrencyCode
		, const FAccelByteModelsCreditUserWalletRequest& CreditUserWalletRequest
		, const THandler<FAccelByteModelsWalletInfo>& OnSuccess, const FErrorHandler& OnError);

	/**
	 * @brief Credit a user wallet by currency code, if the wallet does not exist, it will create a new wallet.
	 *
	 * @param UserId The user who will receive credit.
	 * @param CurrencyCode The currency code.
	 * @param CreditUserWalletRequest The request to credit a user wallet.
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsWalletCreditResponse&.
	 * @param OnError This will be called when the operation fails.
	 */
	void CreditUserWalletV2(const FString& UserId
		, const FString& CurrencyCode
		, const FAccelByteModelsCreditUserWalletRequest& CreditUserWalletRequest
		, const THandler<FAccelByteModelsWalletCreditResponse>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Revoke Entitlement from a User (Many)
	 *
	 * @param UserId The user id who have the entitlements
	 * @param EntitlementIds The ids of the entitlements
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsBulkRevokeEntitlements&.
	 * @param OnError This will be called when the operation fails.
	 */
	void RevokeUserEntitlements(const FString& UserId
		, const TArray<FString>& EntitlementIds
		, const THandler<FAccelByteModelsBulkRevokeEntitlements>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Revoke Entitlement from a User (Single)
	 *
	 * @param UserId The user id who have the entitlement
	 * @param EntitlementId The id of the entitlements
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsEntitlementInfo&.
	 * @param OnError This will be called when the operation fails.
	 */
	void RevokeUserEntitlement(const FString& UserId
		, const FString& EntitlementId
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Consume Entitlement from a User
	 *
	 * @param UserId The user id who have the entitlement
	 * @param EntitlementId The id of the entitlements
	 * @param UseCount How many that will be consumed
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsEntitlementInfo&.
	 * @param OnError This will be called when the operation fails.
	 * @param Options Options of consumed entitlements.
	 * @param RequestId Request id(Optional), A unique tracking ID provided by the developer, can just left it empty if they don't want to track
	 * When a request id is submitted, it will return original successful response
	 */
	void ConsumeUserEntitlement(const FString& UserId
		, const FString& EntitlementId
		, int32 UseCount
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError
		, TArray<FString> Options = {}
		, FString const& RequestId = {});

	/**
	 * @brief Disable Entitlement from a User. Like a revoke, but it can be enabled by calling func EnableUserEntitlement
	 *
	 * @param UserId The user id who have the entitlement
	 * @param EntitlementId The id of the entitlements
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsEntitlementInfo&.
	 * @param OnError This will be called when the operation fails.
	 */
	void DisableUserEntitlement(const FString& UserId
		, const FString& EntitlementId
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError);
	
	/**
	 * @brief Enable Entitlement that has been disabled
	 *
	 * @param UserId The user id who have the entitlement
	 * @param EntitlementId The id of the entitlements
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsBulkRevokeEntitlements&.
	 * @param OnError This will be called when the operation fails.
	 */
	void EnableUserEntitlement(const FString& UserId
		, const FString& EntitlementId
		, const THandler<FAccelByteModelsEntitlementInfo>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Debit a user wallet by currency code, if the wallet does not exist, it will create a new wallet.
	 *
	 * @param UserId The user who will receive credit.
	 * @param WalletId The wallet id.
	 * @param DebitUserWalletRequest The request to debit a user wallet.
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsWalletInfo&.
	 * @param OnError This will be called when the operation fails.
	 */
	// This end point will be deprecated, old wallet id means one currency, but now it only means one wallet, so we wanna use currency and source instead it. 
	void DebitUserWallet(const FString& UserId
		, const FString& WalletId
		, const FAccelByteModelsDebitUserWalletRequest& DebitUserWalletRequest
		, const THandler<FAccelByteModelsWalletInfo>& OnSuccess, const FErrorHandler& OnError);

	/**
	 * @brief FulFill item to a user.
	 *
	 * @param UserId The user who will receive credit.
	 * @param FulfillmentRequest The request to fulfill an item to user.
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsFulfillmentResult&.
	 * @param OnError This will be called when the operation fails.
	 */
	void FulfillUserItem(const FString& UserId
		, const FAccelByteModelsFulfillmentRequest& FulfillmentRequest
		, const THandler<FAccelByteModelsFulfillmentResult>& OnSuccess
		, const FErrorHandler& OnError);

	/**
	 * @brief Get items by multiple Sku.
	 *
	 * @param Skus Sku of the Item.
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsGetBulkItemsBySkus&.
	 * @param OnError This will be called when the operation fails.
	 */
	void BulkGetItemsBySkus(TArray<FString> const& Skus
		, THandler<TArray<FAccelByteModelsBulkGetItemsBySkus>> const& OnSuccess
		, FErrorHandler const& OnError);

	/**
	 * @brief List stores in a namespace.
	 *
	 * @param OnSuccess This will be called when the operation succeeded. The result is const TArray<FAccelByteModelsPlatformStore>&.
	 * @param OnError This will be called when the operation fails.
	 */
	void ListStores(THandler<TArray<FAccelByteModelsPlatformStore>> const& OnSuccess
		, FErrorHandler const& OnError);

	/**
	 * @brief Query items by criteria within a store.
	 *
	 * @param ItemCriteria Struct of item criteria 
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsItemPagingSlicedResult&.
	 * @param OnError This will be called when the operation fails.
	 */
	void QueryItemsByCriteria(const FAccelByteModelsItemCriteriaV2& ItemCriteria
		, THandler<FAccelByteModelsItemPagingSlicedResultV2> const& OnSuccess
		, FErrorHandler const& OnError);

	/**
	 * @brief Query items by criteria within a store, endpoint version 2.
	 *
	 * @param ItemCriteria Struct of item criteria, FAccelByteModelsItemCriteriaV3
	 * @param OnSuccess This will be called when the operation succeeded. The result is const FAccelByteModelsItemPagingSlicedResult&.
	 * @param OnError This will be called when the operation fails.
	 */
	void QueryItemsByCriteriaV2(const FAccelByteModelsItemCriteriaV3& ItemCriteria
		, THandler<FAccelByteModelsItemPagingSlicedResultV2> const& OnSuccess
		, FErrorHandler const& OnError);

private:
	ServerEcommerce() = delete;
	ServerEcommerce(ServerEcommerce const&) = delete;
	ServerEcommerce(ServerEcommerce&&) = delete;
};

} // Namespace GameServerApi
} // Namespace AccelByte
