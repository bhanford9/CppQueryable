// #ifndef CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_SELECTBUILDER_H
// #define CPPQUERYABLE_QUERYABLE_SELECTBUILDERS_SELECTBUILDER_H

// #include <functional>
// #include <memory>

// #include "../InternalQueryable.hpp"

// // template<
// //   typename TStoringOriginal,
// //   typename TStoringCurrent,
// //   template<typename, typename ...> typename TIterable,
// //   typename TIteratingOriginal,
// //   typename TIteratingCurrent,
// //   typename ...TArgs>
// class SelectBuilder
// {
// // protected:
// //   std::shared_ptr<InternalQueryable<TStoringCurrent, TIterable, TIteratingCurrent, TArgs...>> selectedQuery;

// public:
//   // virtual void Build(
//   //   std::shared_ptr<QueryableData<TStoringOriginal, TIterable, TIteratingOriginal, TArgs...>> & data,
//   //   std::function<TStoringCurrent(TIteratingOriginal)> & selector,
//   //   TArgs... iterableArgs) = 0;

//   // std::shared_ptr<InternalQueryable<TStoringCurrent, TIterable, TIteratingCurrent, TArgs...>> Get()
//   // {
//   //   return this->selectedQuery;
//   // }

//   template<
//     template<typename, typename ...> typename TIterable,
//     typename TStoringSource,
//     typename TStoringDestination,
//     typename TAllocatorSource = std::allocator<TStoringSource>,
//     typename TAllocatorDestination = std::allocator<TStoringDestination>>
//   static std::shared_ptr<InternalQueryable<TStoringDestination, TIterable, TStoringDestination, TAllocatorDestination>> BuildDequeSelect(
//     std::shared_ptr<QueryableData<TStoringSource, TIterable, TStoringSource, TAllocatorSource>> & data,
//     std::function<TStoringDestination(TStoringSource)> & selector)
//   {
//     std::shared_ptr<SelectQueryableDequeData<TStoringSource, TStoringDestination, TAllocatorDestination>> selectData =
//       std::make_shared<SelectQueryableDequeData<TOriginal, TStoringDestination, TAllocatorDestination>>(data, selector);

//     std::shared_ptr<DequeInternalQueryable<TStoringDestination, TAllocatorDestination>> dequeQueryable =
//       std::make_shared<DequeInternalQueryable<TStoringDestination, TAllocatorDestination>>(
//         std::move(selectData),
//         QueryableType::Deque);

//     return
//       FutureStd::reinterpret_pointer_cast<InternalQueryable<TStoringDestination, std::deque, TAllocatorDestination>>(
//         dequeQueryable);
//   }
// };

// #endif
